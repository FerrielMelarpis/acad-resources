# Program Description: A simple student record program in PERL with  
#                      input validation using Regular Expressions.
# Copyright (C) 2014 Ferriel Lisandro B. Melarpis
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#this line depends on where perl is located in your file system
#!/usr/bin/perl
use strict;
use warnings;

my @student;
my $scounter = 0;
my $tempsno; 
my $tempsname;
my $tempsbday; 
my $tempscno;
my $tempemail;
my $tempcourse; 
my $tempgrade = 0; 
my $tempunits = 0;

my $i = 0;
my $j = 0;
my $k = 0;
my $h = 0;
my $l = 0;
my $cont;
my $vchoice;

# MAIN PROGRAM
loadStudents();
my $choice = 0;
while($choice != 5){
    menu();

    if($choice == 1){
		screate();
    }elsif($choice == 2){
		sedit();
    }elsif($choice == 3){
		sview();
    }elsif($choice == 4){
		sdelete();
    }elsif($choice == 5){
		ssave();
    }elsif($choice < 1 || $choice > 5){
		print("\e[33m\nInvalid Option.\e[m\n");
    }   
}


# SUBROUTINES

# loadStudents is a subroutine that scans students.txt and stores 
# its data to the dynamic structure of students
sub loadStudents {
	if(open(my $in, "<", "students.txt")){
  	
	$scounter = 0;
	while(<$in>) {
		chomp($student[$scounter]->{"sname"} = <$in>);
		chomp($student[$scounter]->{"sno"} = <$in>);
		chomp($student[$scounter]->{"sbday"} = <$in>);
		chomp($student[$scounter]->{"scno"} = <$in>);
		chomp($student[$scounter]->{"semail"} = <$in>);
		chomp($student[$scounter]->{"ccounter"} = <$in>);
		
		$i = 0;
		while($i < $student[$scounter]->{"ccounter"}) {
			chomp($student[$scounter]->{"subjects"}->[$i]->{"cno"} = <$in>);
			chomp($student[$scounter]->{"subjects"}->[$i]->{"cgrade"} = <$in>);
			chomp($student[$scounter]->{"subjects"}->[$i]->{"cunits"} = <$in>);
			$i++;
		}
		$scounter++;
	}
  
  close $in or die "$in: $!";
  
  }else{
  	warn "\nFile students.txt does not exist. One will be created when this program is exited\n\n";
  }
}

# subroutine for creating a student record
sub screate{
	if($scounter < 10){
		print("\e[32mEnter student number(XXXX-XXXXX):\e[m");
		chomp($tempsno = <STDIN>);	
		if($tempsno =~ /^\d{4}\-\d{5}$/){
		#restriction of unique student numbers
			$k = 0;
			$h = 0;
			while($k < $scounter){
				if($student[$k]->{"sno"} eq $tempsno){
					print("\e[33m\nStudent Number already taken.\e[m\n\n");
					$h = 1;
					$k = $scounter; 
				}

			$k++;
			}
			if($h == 0){
				$student[$scounter]->{"sno"} = $tempsno;
				$k = 0;  
				while($k == 0){
					print("\e[32mEnter name: \e[m");
					chomp($tempsname = <STDIN>);
					
					if($tempsname =~ /^[a-zA-Z]{1,30} [a-zA-Z]{1,30}$/){
						$student[$scounter]->{"sname"} = $tempsname;
						$k++;
					}else{
						print("\e[33m\nInvalid name format.\e[m\n\n")
					}
				}

				$k = 0;  
				while($k == 0){
					print("\e[32mEnter birthday(YYYY-MM-DD):\e[m ");
					chomp($tempsbday = <STDIN>);
					if($tempsbday =~ /^\d{4}\-(0\d|1[012])\-([012]\d|3[01])$/){
						$student[$scounter]->{"sbday"} = $tempsbday;
						$k++;
					}else{
					print("e[33m\nInvalid birthday format.\e[m\n\n")
					}
				}
			
				$k = 0;  
				while($k == 0){
					print("\e[32mEnter contact number: \e[m");
					chomp($tempscno = <STDIN>);
			
					if($tempscno =~ /^((\+63)|0)9\d{9}$/){
						$student[$scounter]->{"scno"} = $tempscno;
						$k++;
					}else{
						print("\e[33m\nInvalid contact number format.\e[m\n\n")
					}
				}

				$k = 0;  
				while($k == 0){
					print("\e[32mEnter email address: \e[m");
					chomp($tempemail = <STDIN>);			
					if($tempemail =~ /^[a-zA-Z][^@]{5,29}@[a-zA-Z]+(\.[a-z]{2,4})+$/){
						$student[$scounter]->{"semail"} = $tempemail;
						$k++;
					}else{
						print("\e[33m\nInvalid email address format.\e[m\n\n")
					}
				}
				$i = 0;
				$j = 0;
				while($i == 0){
					$k = 0;
					while($k == 0){
						print("\e[32mEnter subject: \e[m");
						chomp($tempcourse = <STDIN>);
						if($tempcourse =~ /^[A-Z]{3}([A-Z]?)\s[0-4]?\d?\d/){
							$student[$scounter]->{"subjects"}->[$j]->{"cno"} = $tempcourse;
							$k++;
						}else{
							print("\e[33m\nInvalid course number format.\e[m\n\n");
						}
					}
			
				$k = 0;
				while($k == 0){
					print("\e[32mEnter grade: \e[m");
					chomp($tempgrade = <STDIN>);
					if($tempgrade =~ /^(([12]\.(00|50|25|75))|([345]\.00))$/){
						$student[$scounter]->{"subjects"}->[$j]->{"cgrade"} = $tempgrade;
						$k++;
					}else{
						print("\e[33m\nInvalid course grade format.\e[m\n\n");
					}
				}
			
				$k = 0;
				while($k == 0){
					print("\e[32mEnter units: \e[m");
					chomp($tempunits = <STDIN>);
					if($tempunits =~ /^\d\.00$/){
						$student[$scounter]->{"subjects"}->[$j]->{"cunits"} = $tempunits;
						$k++;
					}else{
						print("\e[33m\nInvalid course units format.\e[m\n\n");
					}
				}

				$j++;

				contmenu();
				chomp($cont = <STDIN>);
					
				if($cont != 1){
					$i++;
				}
			}
			
			$student[$scounter]->{"ccounter"} = $j;
			$scounter++;
			}

		}else{
			print("\e[33m\nInvalid student number.\e[m\n\n");
		}
	}else{
		print("\e[33m\nMaximum number of students reached.\e[m\n\n");
	}
	# sort students by name (bonus)
	@student = sort{$a->{"sname"} cmp $b->{"sname"}}@student;
}
# subroutine for viewing a student record
sub sview {
	if($scounter == 0){
		print("\e[33m\nStudent Record still empty.\e[m\n\n");  
	}else{
		viewmenu();
		chomp($vchoice = <STDIN>);
		# View a student by searching its student number
		if($vchoice == 1){
			print("\e[32mEnter student number: \e[m");
			chomp($tempsno = <STDIN>);
			if($tempsno =~ /^\d{4}\-\d{5}$/){
				$j = 0; 
				$k = 0;
				while($j < $scounter){
					if($tempsno eq $student[$j]->{"sno"}){
					print("\e[32m__________________STUDENT__________________\n");
					print("\e[36mFirst Name: \e[m", $student[$j]->{"sname"}, "\n");
					print("\e[36mStudent Number: \e[m", $student[$j]->{"sno"}, "\n");
					print("\e[36mBirthday: \e[m", $student[$j]->{"sbday"}, "\n");
					print("\e[36mContact Number: \e[m", $student[$j]->{"scno"}, "\n");
					print("\e[36mEmail Address: \e[m", $student[$j]->{"semail"}, "\n\n");
					$i = 0;
					$tempgrade = 0;
					$tempunits = 0;
					while($i < $student[$j]->{"ccounter"}){
						print("\e[36mSubject: \e[m", $student[$j]->{"subjects"}->[$i]->{"cno"}, "\n");
						print("\e[36mGrade:\e[m ", $student[$j]->{"subjects"}->[$i]->{"cgrade"}, "\n");
						print("\e[36mUnits:\e[m ", $student[$j]->{"subjects"}->[$i]->{"cunits"}, "\n");
						$tempgrade += $student[$j]->{"subjects"}->[$i]->{"cgrade"} * $student[$j]->{"subjects"}->[$i]->{"cunits"};
						$tempunits += $student[$j]->{"subjects"}->[$i]->{"cunits"};	
						$i++;
					}
					$student[$j]->{"gwa"} = $tempgrade/$tempunits; 
					print("\e[36m\e[m\nGWA: ", $student[$j]->{"gwa"}, "\n\n");
					print("\e[32m________________________________________________\e[m\n");
					
					$k = 1;
					}
					
					$j++;
				}	
				if($k == 0){
					print("\e[33m\nStudent not found.\e[m\n\n");
				}
			}else{
				print("\e[33m\nInvalid Student Number format.\e[m\n\n")
			}
		# View All
		}elsif($vchoice == 2){
			$j = 0;
			while($j < $scounter){
				print("\e[32m__________________STUDENT__________________\n");
				print("\e[36mFirst Name: \e[m", $student[$j]->{"sname"}, "\n");
				print("\e[36mStudent Number: \e[m", $student[$j]->{"sno"}, "\n");
				print("\e[36mBirthday: \e[m", $student[$j]->{"sbday"}, "\n");
				print("\e[36mContact Number: \e[m", $student[$j]->{"scno"}, "\n");
				print("\e[36mEmail Address: \e[m", $student[$j]->{"semail"}, "\n\n");
				$i = 0;
				$tempgrade = 0;
				$tempunits = 0;
				while($i < $student[$j]->{"ccounter"}){
					print("\e[36mSubject: ", $student[$j]->{"subjects"}->[$i]->{"cno"}, "\n");
					print("\e[36mGrade: ", $student[$j]->{"subjects"}->[$i]->{"cgrade"}, "\n");
					print("\e[36mUnits: ", $student[$j]->{"subjects"}->[$i]->{"cunits"}, "\n\n");
					
					$tempgrade += $student[$j]->{"subjects"}->[$i]->{"cgrade"} * $student[$j]->{"subjects"}->[$i]->{"cunits"};
					$tempunits += $student[$j]->{"subjects"}->[$i]->{"cunits"};
					$i++;
				}
				$student[$j]->{"gwa"} = $tempgrade/$tempunits; 
				print("\e[36mGWA: ", $student[$j]->{"gwa"}, "\n\n");
				print("\e[32m________________________________________________\e[m\n");
				$j++;
			}
		# View students by course number/title 
		}elsif($vchoice == 3){
			print("\e[32mEnter course number: ");
			chomp($tempcourse = <STDIN>);
			
			$j = 0;
			while($j < $scounter){
				$i = 0;
				while($i < $student[$j]->{"ccounter"}){
					if(($student[$j]->{"subjects"}->[$i]->{"cno"} eq $tempcourse) == 1){
						print("\e[32m__________________STUDENT__________________\n");
						print("\e[36mFirst Name: ", $student[$j]->{"sname"}, "\n");
						print("\e[36mStudent Number: ", $student[$j]->{"sno"}, "\n");
						print("\e[36mBirthday: ", $student[$j]->{"sbday"}, "\n");
						print("\e[36mContact Number: ", $student[$j]->{"scno"}, "\n");
						print("\e[36mEmail Address: ", $student[$j]->{"semail"}, "\n\n");
						$h = 0;
						$tempgrade = 0;
						$tempunits = 0;
						while($i < $student[$j]->{"ccounter"}){
							print("\e[36mSubject: ", $student[$j]->{"subjects"}->[$h]->{"cno"}, "\n");
							print("\e[36mGrade: ", $student[$j]->{"subjects"}->[$h]->{"cgrade"}, "\n");
							print("\e[36mUnits: ", $student[$j]->{"subjects"}->[$h]->{"cunits"}, "\n\n");
							$tempgrade += $student[$j]->{"subjects"}->[$h]->{"cgrade"} * $student[$j]->{"subjects"}->[$h]->{"cunits"};
							$tempunits += $student[$j]->{"subjects"}->[$h]->{"cunits"};
							$i++;
						}
						$student[$j]->{"gwa"} = $tempgrade/$tempunits; 
						print("\e[36mGWA: ", $student[$j]->{"gwa"}, "\n\n");
						print("\e[32m________________________________________________\e[m\n");
					}
					$i++;
				}
				$j++;
			}
		}else{
			print("\e[33m\nInvalid Option.\e[m\n\n");
		}
	}
}
# subroutine for editing a student record
# assumption on email :
# I created a regex that does not accept this kind of email > abcdef@asdf@234@gmail.com
# I used /^[a-zA-Z][^@]{5,29}@[a-zA-Z]+(\.[a-z]{2,4})+$/
sub sedit {
	if($scounter == 0){
		print("\e[33m\nStudent Record is still empty.\e[m\n\n");
	}else{
		print("\e[32mEnter student number: ");
		chomp($tempsno = <STDIN>);
		if($tempsno =~ /^\d{4}\-\d{5}$/){
			if($l == 0){
				$j = 0;
				while($j < $scounter){
					if(($student[$j]->{"sno"} eq $tempsno) == 1){
						editmenu();
						chomp($cont = <STDIN>);
			
						# edit name
						if($cont == 1){
							$k = 0;  
							while($k == 0){
								print("\e[32mEnter new name:\e[m ");
								chomp($tempsname = <STDIN>);
								if($tempsname =~ /^[a-zA-Z]{1,30} [a-zA-Z]{1,30}$/){
									$student[$j]->{"sname"} = $tempsname;
									$k++;
								}else{
									print("\e[32m\nInvalid name format.\e[m\n\n")
								}
							}
			
						# edit student number
						}elsif($cont == 2){
							$k = 0;
							while($k == 0){
								print("\e[32mEnter new student number(XXXX-XXXXX):\e[m ");
								chomp($tempsno = <STDIN>);
								if($tempsno =~ /^\d{4}-\d{5}$/){
									$k++;
								}else{
									print("\e[33m\nInvalid Student Number format.\n\n");
								}
							}
			
							if($k == 1){
								$i = 0;
								$h = 0;
								while($i < $scounter){     
									if(($student[$i]->{"sno"} eq $tempsno) == 1){
										print("\e[33m\nStudent number already taken.\e[m\n\n");
										$h = 1;
									}
									$i++;
								}if($h == 0){
									$student[$j]->{"sno"} = $tempsno;
								}
							}elsif($k == 0){
								print("\e[33m\nStudent number format is not allowed.\e[m\n\n");
							}
						# edit birthday 
						}elsif($cont == 3){  
							$k = 0;  
							while($k == 0){
								print("\e[32mEnter new birthday(YYYY-MM-DD):\e[m ");
								chomp($tempsbday = <STDIN>);
								
								if($tempsbday =~ /^\d{4}-[01]\d-[0123]\d$/){
									$student[$j]->{"sbday"} = $tempsbday;
									$k++;
								}else{
									print("\e[33m\nInvalid Birthday format\e[m\n\n");
								}
							}
			
						# edit contact number
						}elsif($cont == 4){
							$k = 0;  
							while($k == 0){
								print("\e[32mEnter new contact number: \e[m");
								chomp($tempscno = <STDIN>);
								if($tempscno =~ /^((\+63)|0)9\d{9}$/){
									$student[$j]->{"scno"} = $tempscno;
									$k++;
								}else{
									print("\e[33m\nInvalid contact number format.\e[m\n\n")
								}
							}
			
						# edit email address
						}elsif($cont == 5){
							$k = 0;  
							while($k == 0){
								print("\e[32mEnter new email address:\e[m ");
								chomp($tempemail = <STDIN>);
								if($tempemail =~ /^[a-zA-Z][^@]{5,29}@[a-zA-Z]+(\.[a-z]{2,4})+$/){
									$student[$j]->{"semail"} = $tempemail;
									$k++;
								}else{
									print("\e[33m\nInvalid email address format.\e[m\n\n")
								}
							}
						# edit subject info
						}elsif($cont == 6){
							$h = 0;
							while($h == 0){
								print("\e[32mInput subject: ");
								chomp($tempcourse = <STDIN>);
								if($tempcourse =~ /^[A-Z]{3}([A-Z]?)\s[0-4]?\d?\d/){
									$h++;
								}else{
									print("\e[33m\nInvalid subject title format.\e[m\n\n");
								}
							}
				
							if($h == 1){
								$i = 0;
								while($i < $student[$j]->{"ccounter"}){
									if(($student[$j]->{"subjects"}->[$i]->{"cno"} eq $tempcourse) == 1){
									subjectmenu();
									chomp($vchoice = <STDIN>);
											
										#edit course number
										if($vchoice == 1){
											$k = 0;
											while($k == 0){
												print("\e[32mEnter new subject title: \e[m");
												$tempcourse = <STDIN>;										
												if($tempcourse =~ /^[A-Z]{3}([A-Z]?)\s[0-4]?\d?\d/){
													$student[$j]->{"subjects"}->[$i]->{"cno"} = $tempcourse;
													$k++;
												}else{
													print("\e[33m\nInvalid subject title format.\e[m\n\n");
												}
											}
										# edit course grade
										}elsif($vchoice == 2){
											$k = 0;
											while($k == 0){
												print("\e[32mEnter new grade: \e[m");
												chomp($tempgrade = <STDIN>);
												if($tempgrade =~ /^(([12]\.(00|50|25|75))|([345]\.00))$/){
													$student[$j]->{"subjects"}->[$i]->{"cgrade"} = $tempgrade;
													$k++;
												}else{
													print("\e[33m\nInvalid subject grade format.\e[m\n\n");
												}
											}
										# edit course units
										}elsif($vchoice == 3){
											$k = 0;
											while($k == 0){
												print("\e[32mEnter new units: \e[m");
												chomp($tempunits = <STDIN>);											
												if($tempunits =~ /^\d\.00$/){
													$student[$j]->{"subjects"}->[$i]->{"cunits"} = $tempunits;
													$k++;
												}else{
													print("\e[33m\nInvalid subject units format.\e[m\n\n");
												}
											}
										}elsif($vchoice == 4){
											$i = $student[$j]->{"ccounter"};
										}else{
											print("\e[33mInvalid Option.\e[m\n");
										}
										$k = 2;
									}elsif(($i == $student[$j]->{"ccounter"} - 1) && $k != 2){
										print("\e[33m\nCourse not found.\e[m\n\n");
									}
									$i++;  
								}
							}
						}
					}elsif($j == $scounter-1 && ($student[$j]->{"sn"} eq $tempsno) != 1){
						print("\e[33m\nStudent not found.\e[m\n\n");
					}
					$j++;
				}
			}
		}else{
			print("\e[33m\nInvalid Student Number Format.\e[m\n\n")
		}
	}
	# update student record's sorting
	@student = sort{$a->{"sname"} cmp $b->{"sname"}}@student;
}

# subroutine for deleting student record
sub sdelete {
	print("\e[32mEnter student number: \e[m");
    chomp($tempsno = <STDIN>);
    
    if($tempsno =~ /^\d{4}\-\d{5}$/){
		$i = 0; 
		while($i < $scounter){
			if($student[$i]->{"sno"} eq $tempsno){

			$j = $student[$i]->{"ccounter"};
			while($j >= 0){
				delete $student[$i]->{"subjects"}->[$j]->{"cno"};
				delete $student[$i]->{"subjects"}->[$j]->{"cgrade"};
				delete $student[$i]->{"subjects"}->[$j]->{"cunits"};
				$j--;
			}
			delete $student[$i]->{"sname"};
			delete $student[$i]->{"sno"};
			delete $student[$i]->{"sbday"};
			delete $student[$i]->{"scno"};
			delete $student[$i]->{"semail"};
			delete $student[$i]->{"gwa"};
			delete $student[$i]->{"ccounter"};
			delete $student[$i]->{"subjects"};
			$student[$i] = $student[0];
			splice @student, 0, 1;
			$i = $scounter;
			}
			$i++;
		}
	    
		if($i == $scounter+1){
			$scounter--;
		}else{
			print("\e[33m\nStudent not found.\e[m\n\n");
		}
    }else{
		print("\e[33m\nInvalid Student Number Format.\e[m\n\n")
    }
  # update the sorting of student record
  @student = sort{$a->{"sname"} cmp $b->{"sname"}}@student;
}

# subroutine for saving the student record.
sub ssave {
	open(my $out, ">", "students.txt") or die "Failed to create students.txt: $!";
	$j = 0;
	while($j < $scounter){
		print $out "\n";
		print $out $student[$j]->{"sname"};
		print $out "\n";
		print $out $student[$j]->{"sno"};
		print $out "\n";
		print $out $student[$j]->{"sbday"};
		print $out "\n";
		print $out $student[$j]->{"scno"};
		print $out "\n";
		print $out $student[$j]->{"semail"};
		print $out "\n";
		print $out $student[$j]->{"ccounter"};
		
		$i = 0;
		while($i < $student[$j]->{"ccounter"}){
			print $out "\n";
			print $out $student[$j]->{"subjects"}->[$i]->{"cno"};
			print $out "\n";
			print $out $student[$j]->{"subjects"}->[$i]->{"cgrade"};
			print $out "\n";
			print $out $student[$j]->{"subjects"}->[$i]->{"cunits"};
			$i++;
		}
		print $out "\n";
		$j++; 
	}
	close $out or die "$out: $!";
}

# subroutine for displaying menu and ask for user's choice of action
sub menu {
	print "\n\e[32m__________\e[1m\e[5mMAIN MENU\e[m\e[32m__________\e[m\n",
    "\e[36m[1] Create Student Record\n",
    "[2] Edit Student Record\n",
    "[3] View Student Record\n",
    "[4] Delete Student Record\n",
    "[5] Exit\e[m\n",
    "\e[32m_____________________________\e[m\n",
    "\e[7m\e[3mEnter choice:\e[m ";
    chomp($choice=<STDIN>);
}

# subroutine for printing menu for editing records
sub editmenu{
	print("\e[32m\n\e[32m__________\e[1m\e[5mEDIT MENU\e[m\e[32m__________\e[m\n",
	"\e[36m[1]Name\n",
	"[2]Student Number\n",
	"[3]Birthday\n",
	"[4]Contact Number\n",
	"[5]Email Address\n",
	"[6]Subject\n",
	"[0]Exit\e[m\n",
	"\e[32m_____________________________\e[m\n",
	"\e[7m\e[3mWhat do you want to edit?\e[m ");
}

# subroutine for printing menu for editing subjects 
sub subjectmenu {
	print("\e[32m\n\e[32m__________\e[1m\e[5mSUBJECT MENU\e[m\e[32m__________\e[m\n",
	"\e[36m[1]Subject title\n",
	"[2]Grade\n",
	"[3]Number of units\n",
	"[4]Exit\e[m\n",
	"\e[32m_____________________________\e[m\n",
	"\e[7mEnter choice:\e[m ");
}

# menu for asking continuation
sub contmenu {
	print("\e[32m__________\e[1m\e[5mCONTINUE?\e[m\e[32m__________\e[m\n",
	"\e[36mDo you want to input more subjects?\n",
	"[1]Yes\n",
	"[2]No\n",
	"\e[32m_____________________________\e[m\n",
	"\e[7mEnter choice: \e[m");
}

# menu for view
sub viewmenu {
	print("\e[32m__________\e[1m\e[5mVIEW MENU\e[m\e[32m__________\e[m\n",
	"\e[36m[1]View a student\n",
	"[2]View all\n",
	"[3]View students by subject\n",
	"\e[32m_____________________________\e[m\n",
	"\e[7mEnter option: \e[m");
}
# RED = "\e[31m";
# GRN = "\e[32m";
# YEL = "\e[33m";
# BLU = "\e[34m";
# MAG = "\e[35m";
# ITA = "\e[3m";
# 
# BRED = "\e[41m";
# BGRN = "\e[42m";
# BYEL = "\e[43m";
# BBLU = "\e[44m";
# BMAG = "\e[45m";
# 
# BLD = "\e[1m";
# INV = "\e[7m";
# CLR = "\e[m";
# BLK = "\e[5m";
# UND = "\e[4m";
#END OF PROGRAM
