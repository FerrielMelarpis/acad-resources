#!/usr/bin/perl

use strict;
use warnings;

my @student = ();	#declare array of students
my %studentinfo = ();	#declare hash for student informations
my @subjList = ();	#declare array for subjects taken
my %subjInfo = ();	#declare hash for infos of subjects taken

my $choice = 5;
my $index;
my $name;
my $studentNumber;
my $birthdate;
my $contactNumber;
my $Eadd;
my $courseNumber;
my $courseCredit;
my $grade;
my $choice2 = 0;

push @student, \%studentinfo;	#creates a hash within a list
push @subjList, \%subjInfo;	#creates a hash within a list

$studentinfo{"subjList"} = \@subjList;

until($choice == 0){
print "Main Menu: 
";
print "		[1] Create Student Record
		[2] Edit Student Record
		[3] View Student Record
		[0] Exit
";

print "Enter choice: ";
$choice = <STDIN>;

if($choice == 1) {
	print "\tName: ";
	$name = <STDIN>;
	chomp($name);
	print "\tStudent Number: ";
	$studentNumber = <STDIN>;
	chomp($studentNumber);
	print "\tBirthday :";
	$birthdate = <STDIN>;
	chomp($birthdate);
	print"\tContact Number: ";
	$contactNumber = <STDIN>;
	chomp($contactNumber);
	
	push @student, $studentinfo{"name"} = $name;
	push @student, $studentinfo{"studentNumber"} = $studentNumber;
	push @student, $studentinfo{"birthdate"} = $birthdate;
	push @student, $studentinfo{"contactnum"} = $contactNumber;
	
	until($choice2 == 2)
	{
		print "[ Subject ]\n";
		print "\tCourse Number: ";
		$courseNumber = <STDIN>;
		chomp($courseNumber);
		print "\tCours Credit: ";
		$courseCredit = <STDIN>;
		chomp($courseCredit);
		print "\tGrade: ";
		$grade = <STDIN>;
		chomp($grade);
		
		push @subjList, $subjInfo{"num"} = $courseNumber;
		push @subjList, $subjInfo{"credit"} = $courseCredit;
		push @subjList, $subjInfo{"grade"} = $grade;
		
		print "Enter another subject?\n";
		print "[1] Yes\n";
		print "[2] No\n";
		print "Choice: ";
		$choice2 = <STDIN>;
	}	
	
	
	push @student,  $studentinfo{"subjects"} = \@subjList;
	
print $student[0]->{"name"};
print $student[0]->{"studentNumber"};
print $student[0]->{"birthdate"};
print $student[0]->{"contactnum"};
print $student[0]->{"subjList"}->[0]->{"num"};
print $student[0]->{"subjList"}->[0]->{"credit"};
print $student[0]->{"subjList"}->[0]->{"grade"};
}
}
