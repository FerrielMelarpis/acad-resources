use strict;
use warnings;
use Data::Dumper;
my @students = ();
load();
# print Dumper(@students);
mainMenu();

sub mainMenu{
    my $choice=-1;
    while($choice != 0){
        print "Menu:\n  [0] Exit \n  [1] Add Student \n  [2] Edit Student \n  [3] View Student/s \n  [4] Search for Student \n  [5] Delete Student\nChoice:";
        chomp($choice=<STDIN>);
        if($choice == 1){
            add();
        } elsif($choice == 2){
        } elsif($choice == 3){
            my $choice;
            print "View Students:\n  [0] View All Students\n  [1] View One Student\n  Choice:";
            chomp($choice=<STDIN>);
            if($choice==0){
                my $stcount = $#students;
                print "Students: \n";
                for(my $i=0;$i<=$stcount;$i++){
                    viewStudent($i);
                }
            } elsif($choice==1){
                my $sntmp = searchSNum();
                if($sntmp >= 0){
                    viewStudent($sntmp);
                }
            }
           
        } elsif($choice == 4){
        } elsif($choice == 5){
        }
    }
}

sub load{
    open(my $file, "<", "data.txt") or return;
    my $c = 0;
    while(<$file>){
        if($_ =~ /(?<name>[^|]+)\|(?<snum>[^|]+)\|(?<bday>[^|]+)\|(?<cnum>[^|]+)\|(?<email>[^|]+)\|(?<subjects>.*)/gi){
            $students[$c]->{"name"} = $+{"name"};
            $students[$c]->{"studentNumber"} = $+{"snum"};
            $students[$c]->{"birthdate"} = $+{"bday"};
            $students[$c]->{"contactNumber"} = $+{"cnum"};
            $students[$c]->{"emailAddress"} = $+{"email"};
            my @sstemp = split(",",$+{"subjects"});
            my $sc = 0;
            foreach my $subs (@sstemp){
                my @stemp = split(":", $subs);  
                $students[$c]->{"subjects"}[$sc]->{"courseNumber"} = $stemp[0];
                $students[$c]->{"subjects"}[$sc]->{"courseCredit"} = $stemp[1];
                $students[$c]->{"subjects"}[$sc]->{"courseGrade"} = $stemp[2];
                $sc++;
            }
            $students[$c]->{"subjectCount"} = $sc;
            $c++;
        }
    }
    close($file);
}

sub add{
    my $c = $#students+1;
    print "Name: ";
    chomp($students[$c]->{"name"} = <STDIN>);
    print "Student Number: ";
    chomp($students[$c]->{"studentNumber"} = <STDIN>);
    print "Birthdate [yy-mm-dd]: ";
    chomp($students[$c]->{"birthdate"} = <STDIN>);
    print "Contact Number: ";
    chomp($students[$c]->{"contactNumber"} = <STDIN>);
    print "Email Address: ";
    chomp($students[$c]->{"emailAddress"} = <STDIN>);
    print "Subjects:\n";
    my $count = 0;
    for(my $choice='y';$choice ne 'n';$count++){
        print("  Course Number: ");
        chomp($students[$c]->{"subjects"}[$count]->{"name"} = <STDIN>);
        print("  Number of Units: ");
        $students[$c]->{"subjects"}[$count]->{"courseCredit"} = int(<STDIN>);
        print("  Grade : ");
        $students[$c]->{"subjects"}[$count]->{"courseGrade"} = (<STDIN>)+0.00;
        print("Do you want to add another subject [y/n]? ");
        $count++; 
        chomp($choice = <STDIN>);
    }
    $students[$c]->{"subjectCount"} = $count;
}

sub searchSNum{
    my $snum;
    my $choice = 'y';
    while($choice ne 'n'){
        print("Enter Student Number: ");
        chomp($snum = <STDIN>);
        for(my $s = 0; $s<=$#students; $s++){
            if($students[$s]->{"studentNumber"} eq $snum){
                return $s;
            }
        }
        print("Not found. Try again [y/n]?");
        chomp($choice = <STDIN>);
    }
    return -1;
}

sub viewStudent{
    my $sid = $_[0];
    print "\n  Name: " . $students[$sid]->{"name"} . "\n";
    print "  Student Number: " . $students[$sid]->{"studentNumber"} . "\n";
    print "  Birthdate: " . $students[$sid]->{"birthdate"} . "\n";
    print "  Contact Number: " . $students[$sid]->{"contactNumber"} . "\n";
    print "  Email Address: " . $students[$sid]->{"emailAddress"} . "\n";
    print "  Subjects: \n";
#     print Dumper($students[$sid]->{"subjects"});
#     my @test = $students[$sid]->{"subjects"};
#     print Dumper($students[$sid]->{"subjects"});
    my $tunits=0;
    my $unitxgrade=0.0;
    for(my $i=0;$i<$students[$sid]->{"subjectCount"};$i++){
        my $units = $students[$sid]->{"subjects"}[$i]->{"courseCredit"};
        my $grade = $students[$sid]->{"subjects"}[$i]->{"courseGrade"};
        print "    Name: " . $students[$sid]->{"subjects"}[$i]->{"courseNumber"} . " Units: " . $units . " Grade: " . $grade . "\n";
        $tunits+=$units;
        $unitxgrade+=$units*$grade;
    }
    print "  General Weighted Average: " . $unitxgrade/$tunits . "\n\n";
}

sub printSnums{
    foreach my $s (@students){
        print $s->{"studentNumber"} . ":" . $s->{"name"} . "\n";
    }
}