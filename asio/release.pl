#!/usr/bin/perl -w

use strict;
use Cwd qw(abs_path getcwd);
use Date::Format;
use File::Path;
use File::Copy;
use File::Basename;

our $version_major;
our $version_minor;
our $version_sub_minor;
our $asio_name;

sub print_usage_and_exit
{
  print("usage: ./release.pl <version>\n");
  print("   or: ./release.pl <version> --version-only\n");
  print("   or: ./release.pl --package-asio\n");
  print("\n");
  print("examples:\n");
  print("  create new version and build packages for asio:\n");
  print("    ./release.pl 1.2.0\n");
  print("  create new version:\n");
  print("    ./release.pl 1.2.0 --version-only\n");
  print("  create packages for asio only:\n");
  print("    ./release.pl --package-asio\n");
  exit(1);
}

sub determine_version($)
{
  my $version_string = shift;
  if ($version_string =~ /^([0-9]+)\.([0-9]+)\.([0-9]+)$/)
  {
    our $version_major = $1;
    our $version_minor = $2;
    our $version_sub_minor = $3;

    our $asio_name = "asio";
    $asio_name .= "-$version_major";
    $asio_name .= ".$version_minor";
    $asio_name .= ".$version_sub_minor";
  }
  else
  {
    print_usage_and_exit();
  }
}

sub determine_version_from_configure()
{
  my $from = "configure.ac";
  open(my $input, "<$from") or die("Can't open $from for reading");
  while (my $line = <$input>)
  {
    chomp($line);
    if ($line =~ /^AC_INIT\(\[asio\],\[(.*)\]\)$/)
    {
      our $asio_name = "asio-$1";
      last;
    }
  }
}

sub update_configure_ac
{
  # Open the files.
  my $from = "configure.ac";
  my $to = $from . ".tmp";
  open(my $input, "<$from") or die("Can't open $from for reading");
  open(my $output, ">$to") or die("Can't open $to for writing");

  # Copy the content.
  while (my $line = <$input>)
  {
    chomp($line);
    if ($line =~ /^AC_INIT\(\[asio\].*\)$/)
    {
      $line = "AC_INIT([asio],[";
      $line .= "$version_major.$version_minor.$version_sub_minor";
      $line .= "])";
    }
    print($output "$line\n");
  }

  # Close the files and move the temporary output into position.
  close($input);
  close($output);
  move($to, $from);
  unlink($to);
}

sub update_readme
{
  # Open the files.
  my $from = "README";
  my $to = $from . ".tmp";
  open(my $input, "<$from") or die("Can't open $from for reading");
  open(my $output, ">$to") or die("Can't open $to for writing");

  # Copy the content.
  while (my $line = <$input>)
  {
    chomp($line);
    if ($line =~ /^asio version/)
    {
      $line = "asio version ";
      $line .= "$version_major.$version_minor.$version_sub_minor";
    }
    elsif ($line =~ /^Released/)
    {
      my @time = localtime;
      $line = "Released " . strftime("%A, %d %B %Y", @time) . ".";
    }
    print($output "$line\n");
  }

  # Close the files and move the temporary output into position.
  close($input);
  close($output);
  move($to, $from);
  unlink($to);
}

sub update_asio_version_hpp
{
  # Open the files.
  my $from = "include/asio/version.hpp";
  my $to = $from . ".tmp";
  open(my $input, "<$from") or die("Can't open $from for reading");
  open(my $output, ">$to") or die("Can't open $to for writing");

  # Copy the content.
  while (my $line = <$input>)
  {
    chomp($line);
    if ($line =~ /^#define ASIO_VERSION /)
    {
      my $version = $version_major * 100000;
      $version += $version_minor * 100;
      $version += $version_sub_minor + 0;
      $line = "#define ASIO_VERSION " . $version;
      $line .= " // $version_major.$version_minor.$version_sub_minor";
    }
    print($output "$line\n");
  }

  # Close the files and move the temporary output into position.
  close($input);
  close($output);
  move($to, $from);
  unlink($to);
}

sub build_asio_doc
{
  $ENV{BOOST_ROOT} = abs_path("../boost");
  system("rm -rf doc");
  my $bjam = abs_path(glob("../boost/bjam"));
  chdir("src/doc");
  system("$bjam clean");
  system("rm -rf html");
  system("$bjam");
  chdir("../..");
  mkdir("doc");
  system("cp -vR src/doc/html/* doc");
}

sub make_asio_packages
{
  our $asio_name;
  system("./autogen.sh");
  system("./configure");
  system("make dist");
  system("tar tfz $asio_name.tar.gz | sed -e 's/^[^\\/]*//' | sort -df > asio.manifest");
}

(scalar(@ARGV) == 1 || scalar(@ARGV) == 2) or print_usage_and_exit();
my $new_version = 1;
my $package_asio = 1;
if ($ARGV[0] eq "--package-asio")
{
  $new_version = 0;
}
if (scalar(@ARGV) == 2 && $ARGV[1] eq "--version-only")
{
  $package_asio = 0;
}

if ($new_version)
{
  determine_version($ARGV[0]);
  update_configure_ac();
  update_readme();
  update_asio_version_hpp();
}
else
{
  determine_version_from_configure();
}

if ($package_asio)
{
#build_asio_doc();
  make_asio_packages();
}
