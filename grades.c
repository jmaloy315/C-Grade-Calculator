/*Jack Maloy, 116329200, jmaloy*/
#include <math.h>
#include <stdio.h>

double numeric_value(int num_drop, int penalty, int assignments[], 
		     int total_assignments);
double mean(int assignments[], int num_assignments, int penalty);
double std(int assignments[], int num_assignments, int penalty);

int main(){
  int asgn[200] = {0}, print_copy[200] = {0};
  int total_assignments, penalty, drop;
  char stat;
  int i, count = 1;
  double numeric_score, mean_value, std_value;
 
  scanf("%d %d %c\n", &penalty, &drop, &stat);
  scanf("%d\n", &total_assignments);
 
  for(i=0; i<total_assignments*4; i+=4){
    scanf("%d,%d,%d,%d\n", &asgn[i],  &asgn[i+1],  &asgn[i+2],  &asgn[i+3]);
  }

  for(i=1; i<=total_assignments*4; i++){
    print_copy[i] = asgn[i];
  }
  
  if(drop >= 0 && drop < total_assignments){
    numeric_score = numeric_value(drop, penalty, print_copy, total_assignments);
  }else{
    numeric_score = 0;
  }
  
  printf("Numeric Score: %5.4f\n", numeric_score);
  printf("Points Penalty Per Day Late: %d\n", penalty);
  printf("Number of Assignments Dropped: %d\n", drop);

  printf("Values Provided:\n");
  printf("Assignment, Score, Weight, Days Late\n");

  while(count <= total_assignments){
    for(i = 0; i < total_assignments*4; i += 4){
      if(asgn[i] == count){
	printf("%d, %d, %d, %d\n", asgn[i], asgn[i+1], asgn[i+2], asgn[i+3]);
      }
    }
    count = count + 1;
  }
  
  if(stat == 'Y' || stat == 'y'){
    mean_value = mean(asgn, total_assignments, penalty);
    std_value = std(asgn, total_assignments, penalty);
   
    printf("Mean: %5.4f, Standard Deviation: %5.4f\n", mean_value, std_value);
  }
  return 0;
}

/*The mean function takes in an array of assignment data, an int
representing the number assignments, and an int representing the
late penalty. This function returns the mean value of the scores
of all assignments.*/
double mean(int assignments[], int num_assignments, int penalty){
  int i;
  double numerator=0;

  for(i=0; i<num_assignments*4; i+=4){
    numerator += (assignments[i+1] - (assignments[i+3]*penalty));
  }
  return numerator/num_assignments;
}

/*The numeric value takes in the number of assignments to be dropped,
the penalty for late assignments, an array containing the data of all
assignments, and the total number of assignments. This function returns
the student's final score with respect to assignments dropped and late
penalties.*/
double numeric_value(int num_drop, int penalty, int assignments[],
		     int total_assignments){
  int i, adjusted_score;
  double numerator = 0, total_weights = 0, final_score;
 
  /*Assignments being dropped*/
  if(num_drop > 0){
  int min, temp, count=0, index=0;
 
  while(count++ < num_drop){
    min = assignments[1] * assignments[2];
    for(i=0; i< (total_assignments*4); i += 4){
      temp = assignments[i+1] * assignments[i+2];
      if(temp != 0){
	if(temp < min){
	  min = temp;
	  index = i;
	}else if(temp==min && i < index){
	  min = temp;
	  index = i;
	}
      }
    }
    assignments[index + 2] = 0;
   }
  }

  for(i=0; i<total_assignments*4; i+=4){
    total_weights += assignments[i+2];
  }

  if(total_weights > 100){
    printf("ERROR: Invalid values provided\n");
    return 0;
  }else{
    for(i=0; i<total_assignments*4; i+=4){
      adjusted_score = assignments[i+1] - (assignments[i+3] * penalty);
	if(adjusted_score > 0){
	  numerator += adjusted_score * assignments[i+2];
	}
    }
    final_score = numerator/total_weights;
  }
  return final_score;
}

/*The std function takes in an array of all the assignment data, 
the number of assignments, and the late penalty. It calculates 
the standard deviation of all assignments.*/
double std(int assignments[], int num_assignments, int penalty){
  int i, grade;
  double res, numerator=0, mu = mean(assignments, num_assignments, penalty);

  for(i=0; i<num_assignments*4; i+=4){
    grade = assignments[i+1] - (assignments[i+3] * penalty);
    numerator += pow((grade-mu), 2);
  }
  res = numerator/num_assignments;
  return sqrt(res);
}
