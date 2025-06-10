#include<stdio.h>
#include<string.h>

struct subject {
	
	char subject_ID [ 20 ] ;
	char subject_name [ 100 ] ;
	int credit ;
	int score ;

};

struct studentGPA{
	
	char firstname[ 20 ] ;
	char lastname[ 20 ] ;
	char semester[ 10 ] ;
	int count_subject ;
	struct subject subjects[ 10 ] ;
	
};
typedef struct studentGPA stdgpa ;

int Score_To_Grade_Calculator( int Cal_score ) ;
float Score_To_Grade_Point_Calculator( int Cal_score ) ;
float GPA_Calculator( stdgpa student ) ;

int main () {

//--------------------------------------------- declare Section ---------------------------------------------//
	
	stdgpa student ;
	int total_credits = 0 ;
	
//---------------------------------------------- Input Section ----------------------------------------------//	

	printf( "This program was designed by Pongpan Laowaphong [66543206019-2] \n\n" ) ;
	
	printf( "Please enter your name [Ex. Pongpan Laowaphong] : " ) ;
	scanf( "%s %s", student.firstname, student.lastname ) ;
	
	printf( "Please enter your semester [Ex. 1/2567] : " ) ;
	scanf( "%s", student.semester ) ;
	
	printf( "How many subjects were you enrolled in this semester ? [Ex. 1] : " ) ;
	scanf( "%d", &student.count_subject ) ;
	
	
	for( int i = 0 ; i < student.count_subject ; i++ ) {
		
		printf( "[Subject : %d] Please enter your subject ID [Ex. ENGCE106] : ", i + 1 ) ;
		scanf( "%s", student.subjects[i].subject_ID ) ;
		
		printf( "[Subject : %d] Please enter your subject name [Ex. Data commucation and networks] : ", i + 1 ) ;
		scanf( " %[^\n]", student.subjects[i].subject_name ) ;
		
		do{
			
			printf( "[Subject : %d] Please enter your credit [Ex. 3] : ", i + 1 ) ;
			scanf( "%d", &student.subjects[i].credit ) ;
			
			if( student.subjects[i].credit < 1 || student.subjects[i].credit > 6 ) {
				
				printf( "Please enter number between 1 - 6 \n\n" ) ;
		
			}
			
		}while( student.subjects[i].credit < 1 || student.subjects[i].credit > 6 ) ;
		
		total_credits = total_credits + student.subjects[i].credit ;
							
		do{
			
			printf( "[Subject : %d] Please enter your score [Ex. 80] : ", i + 1 ) ;
			scanf( "%d", &student.subjects[i].score ) ;
			
			if( student.subjects[i].score < 0 || student.subjects[i].score > 100 ) {
				
				printf( "Please enter number between 0 - 100 \n\n" ) ;
		
			}		
				
		}while( student.subjects[i].score < 0 || student.subjects[i].score > 100 ) ;
		
		printf( "\n" ) ;
		
	}
	
//---------------------------------------------- Output Section ----------------------------------------------//

	printf( "\n" ) ;
	printf( "|---------------------------- Result of calculation ----------------------------|") ;
	printf( "\n\n" ) ;
	
	printf( "Name : %s %s \n", student.firstname, student.lastname ) ;
	printf( "Semester : %s \n", student.semester ) ;
	printf( "Number of enrolled subjects : %d \n\n", student.count_subject ) ;
	
	for( int i = 0 ; i < student.count_subject ; i++ ) {
		
		printf( "[Subject : %d] Subject ID : %s \n", i + 1, student.subjects[i].subject_ID ) ;
		printf( "[Subject : %d] Subject Name : %s \n", i + 1, student.subjects[i].subject_name ) ;
		printf( "[Subject : %d] Subject Credit : %d \n", i + 1, student.subjects[i].credit ) ;
		printf( "[Subject : %d] Subject Score : %d \n", i + 1, student.subjects[i].score ) ;
		printf( "[Subject : %d] Student Grade : ", i + 1 ) ;
		Score_To_Grade_Calculator( student.subjects[i].score ) ;
		printf( "[Subject : %d] Student Grade [Point] : %.1f\n", i + 1, Score_To_Grade_Point_Calculator( student.subjects[i].score ) ) ;
		printf( "\n" ) ;

	}

	printf( "Total GPA : %.2f \n", GPA_Calculator(student) ) ;
	printf( "Total of credits : %d \n", total_credits ) ;
	
	printf( "\n" ) ;
	printf( "|------------------------------- End of processing --------------------------------|") ;
	printf( "\n" ) ;
	
	return 0 ;
	
}//end function

int Score_To_Grade_Calculator( int Cal_score ) {
	
	if( Cal_score >= 0 && Cal_score < 50 ) {
		
		printf( "Grade F" ) ;
		printf( "\n" ) ;
		
	}else if ( Cal_score >= 50 && Cal_score < 55 ) {
		
		printf( "Grade D" ) ;
		printf( "\n" ) ;
		
	}else if ( Cal_score >= 55 && Cal_score < 60 ) {
		
		printf( "Grade D+" ) ;
		printf( "\n" ) ;
		
	}else if ( Cal_score >= 60 && Cal_score < 65 ) {
		
		printf( "Grade C" ) ;
		printf( "\n" ) ;
		
	}else if ( Cal_score >= 65 && Cal_score < 70 ) {
		
		printf( "Grade C+" ) ;
		printf( "\n" ) ;
		
	}else if ( Cal_score >= 70 && Cal_score < 75 ) {
		
		printf( "Grade B" ) ;
		printf( "\n" ) ;
		
	}else if ( Cal_score >= 75 && Cal_score < 80 ) {
		
		printf( "Grade B+" ) ;
		printf( "\n" ) ;
		
	}else if ( Cal_score >= 80 && Cal_score <= 100 ) {
		
		printf( "Grade A" ) ;
		printf( "\n" ) ;
		
	}else {
		
		printf( "Score was error. Please try again !!!" ) ;
		
	}
	
}//end function

float Score_To_Grade_Point_Calculator( int Cal_score ) {

	float Cal_grade	;

	if( Cal_score >= 0 && Cal_score < 50 ) {
	
		Cal_grade = 0 ;
		
	}else if ( Cal_score >= 50 && Cal_score < 55 ) {
		
		Cal_grade = 1 ;	
		
	}else if ( Cal_score >= 55 && Cal_score < 60 ) {
		
		Cal_grade = 1.5 ;	
		
	}else if ( Cal_score >= 60 && Cal_score < 65 ) {
		
		Cal_grade = 2 ;
		
	}else if ( Cal_score >= 65 && Cal_score < 70 ) {
		
		Cal_grade = 2.5 ;
		
	}else if ( Cal_score >= 70 && Cal_score < 75 ) {
		
		Cal_grade = 3 ;
		
	}else if ( Cal_score >= 75 && Cal_score < 80 ) {
		
		Cal_grade = 3.5 ;
		
	}else if ( Cal_score >= 80 && Cal_score <= 100 ) {
		
		Cal_grade = 4 ;
		
	}else {
		
		printf( "Score was error. Please try again !!!" ) ;
		
	}
	
	return Cal_grade ;

}//end function

float GPA_Calculator( stdgpa student ) {
	
	int total_credits = 0 ;
	float total_grade_points = 0.0 ;
	
	for( int i = 0 ; i < student.count_subject ; i++ ) {
		
		float grade_point = Score_To_Grade_Point_Calculator( student.subjects[i].score ) ;
		total_credits = total_credits + student.subjects[i].credit ;
		total_grade_points = total_grade_points + grade_point * student.subjects[i].credit ;
		
	}
	
	return total_grade_points / total_credits ;
	
}
