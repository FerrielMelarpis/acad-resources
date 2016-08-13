#!/usr/bin/perl
use strict;
use warnings;

my @student;

sub main_menu{
    print "\e[32m__________\e[1m\e[5mMain Menu\e[m\e[32m__________\e[m\n",
    "\e[36m[1] Create Student Record\n",
    "[2] Edit Student Record\n",
    "[3] View Student Record\n",
    "[4] Delete Student Record\n",
    "[5] Exit\e[m\n",
    "\e[32m_____________________________\e[m\n",
    "\e[7m\e[3mEnter choice:\e[m ";
    my $c = <STDIN>;
    chomp $c;
    return $c;
}

sub createStudent{
    my $i = $#student+1;
    if($i<10){
    print " ==>Name: ";
    chomp($student[$i]->{"name"}=<STDIN>);
    print " ==>Student Number: ";
    chomp($student[$i]->{"studentNumber"}=<STDIN>);
    print " ==>Birthday (YYYY-MM-DD): ";
    chomp($student[$i]->{"birthdate"}=<STDIN>);
    print " ==>Contact Number: ";
    chomp($student[$i]->{"contactNumber"}=<STDIN>);
    print " ==>Email Address: ";
    chomp($student[$i]->{"emailAddress"}=<STDIN>);
    print "::Subjects::\n";
    my $j=0;
    my $in="yes";
        until($in eq "no"){
            print "Course Number: ";
            chomp($student[$i]->{"subjects"}->[$j]->{"courseNumber"} = <STDIN>);
            print "Course Credit: ";
            chomp($student[$i]->{"subjects"}->[$j]->{"courseCredit"} = <STDIN>);
            print "Course Grade: ";
            chomp($student[$i]->{"subjects"}->[$j]->{"courseGrade"} = <STDIN>);
            $j++;
            print "Enter another subject? (yes/no) : ";
            chomp($in=<STDIN>);
        }
    }else{
        print "List of student records already full.\n";
    }
}

sub findStudent{
    for(my $i=0; $i<$#student+1;$i++){
        if($student[$i]->{"studentNumber"} eq $_[0]){
            return $i;
        }
    }
    return -1;
}

sub viewStudent{
    if($_[0]==-1){
        print "Student not found.\n";
    }else{
        print "Name: "
        print "Student Number"
    }
}

sub viewAll{
    
}

sub view{
    print "->View Student Record\n",
    "[1] View one student\n",
    "[2] View all students\n",
    "Enter choice: ";
    my $choice;
    chomp($choice=<STDIN>);
    if($choice == 1){
        print "Enter student number>> ";
        my $sn = <STDIN>;
        chomp $sn;
        my $ret = findStudent($sn);
        viewStudent($ret);
    }elsif($choice == 2){
    }else{
        print "Invalid choice!\n";
    }
}

# sub edit{
#     my $in;
#     print "Instruction: hit enter if you don't want to change\n",
#     "the specific attribute.\n";
#     print "Name: "; chomp($in = <STDIN>);
#     if($in ne ""){ $_[0]->{"name"} = $in;}
#     print "Student Number: "; chomp($in = <STDIN>);
#     if($in ne ""){ $_[0]->{"studentNumber"} = $in;}
#     print "Birthdate: "; chomp($in = <STDIN>);
#     if($in ne ""){ $_[0]->{"birthdate"} = $in;}
#     print "Contact Number: "; chomp($in = <STDIN>);
#     if($in ne ""){ $_[0]->{"contactNumber"} = $in;}
#     print "Email Address: "; chomp($in = <STDIN>);
#     if($in ne ""){ $_[0]->{"emailAddress"} = $in;}
#     print "Subjects: "; chomp($in = <STDIN>);
#     if($in ne ""){ 
#         for(my $i=0; $i<$#;$i++) {
#             print "Subject $i";
#             print "Course Number: "; chomp($in=<STDIN>);
#             if($in ne ""){ $s->{"courseNumber"} = $in; }
#             print "Course Creditr: "; chomp($in=<STDIN>);
#             if($in ne ""){ $s->{"courseCredit"} = $in; }
#             print "Course Grade: "; chomp($in=<STDIN>);
#             if($in ne ""){ $s->{"courseGrade"} = $in; }
#         }
#     }
# }

my $choice = 0;
until($choice == 5){
    $choice = main_menu();
    if($choice == 1){
        print "->Create Student Record\n";
        createStudent();
    }elsif($choice == 2){
        print "->Edit Student Record\n",
        "Enter student number>> ";
        my $sn = <STDIN>;
        chomp $sn;
        edit($sn);
    }elsif($choice == 3){
        view();
    }elsif($choice == 4){
        
    }elsif($choice == 5){
        print "Thank you for using this program :)\n";
    }
}