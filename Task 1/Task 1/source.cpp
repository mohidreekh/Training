

int readNumber(string message, int min = INT_MIN, int max = INT_MAX)
{
    int num;

    do
    {
        cout << message;
        cin >> num;

        if (num < min || num > max)
        {
            cout << "Invalid number! Enter a value between "
                << min << " and " << max << endl;
                
        }

    } while (num < min || num > max);

    return num;
}


char getGrade(int mark)
{
    if (mark >= 90)
    {
        return 'A';
    }
    else if (mark >= 80)
    {
        return 'B';
    }
    else if (mark >= 70)
    {
        return 'C';
    }
    else if (mark >= 60)
    {
        return 'D';
    }
    else
    {
        return 'E';
    }
}

int** collectStudentsMarks(int numberOfStudents)
{
    int** arr = new int* [numberOfStudents];

    for (int i = 0; i < numberOfStudents; i++)
    {
        arr[i] = new int[3]; // 3 marks for each student

        cout << "student" << i + 1 << endl;

        for (int j = 0; j < 3; j++)
        {
            int mark = readNumber("Enter the student mark " + to_string(j + 1) + " : ", 0, 100);

            arr[i][j] = mark;
        }
    }

    return arr;
}

void printAllStudents(int** marks, int numOfstudents) {
    for (int i = 0; i < numOfstudents; i++) {
        cout << "student" << i + 1 << " : ";

        for (int j = 0; j < 3; j++)
        {
            cout << getGrade(marks[i][j]) << " ";
        }

        cout << endl;
    }
}


void printStudentsStatistics(int** marks, int numberOfStudents)
{
    for (int i = 0; i < numberOfStudents; i++)
    {
        int highest = marks[i][0];
        int lowest = marks[i][0];
        int sum = 0;

        for (int j = 0; j < 3; j++)
        {
            if (marks[i][j] > highest)
                highest = marks[i][j];

            if (marks[i][j] < lowest)
                lowest = marks[i][j];

            sum += marks[i][j];
        }

        double average = (double)sum / 3;

        cout << "\nStudent " << i + 1 << endl;
        cout << "Highest Grade: " << getGrade(highest) << endl;
        cout << "Lowest Grade : " << getGrade(lowest) << endl;
        cout << "Average Grade: " << getGrade(average) << endl;

    }

}


int numOfPassingStudents(int** marks, int numberOfStudents) {
    int count = 0;

    for (int i = 0; i < numberOfStudents; i++)
    {
        int sum = 0;

        for (int j = 0; j < 3; j++)
        {
            sum += marks[i][j];
        }

        double average = (double)sum / 3;

        if (average >= 50)
            count++;
    }

    return count;
}


int numOfFailingStudents(int** marks, int numberOfStudents) {
    return numberOfStudents - numOfPassingStudents(marks, numberOfStudents);
}


int main()
{

    int numberOfStudents = readNumber("Enter the number of students: ", 1);

    int** marks = collectStudentsMarks(numberOfStudents);



    int choice;

    do {

        cout << "\n\n1_Show all students." << endl;
        cout << "2_Show Statistics." << endl;
        cout << "3_exit\n\n" << endl;

        choice = readNumber("chose number: ", 1, 3);


        if (choice == 1) {
            printAllStudents(marks, numberOfStudents);
        }
        else if (choice == 2)
        {
            printStudentsStatistics(marks, numberOfStudents);
            cout << "\nNumber of passing students: " << numOfPassingStudents(marks, numberOfStudents) << endl;
            cout << "\nNumber of failing students: " << numOfFailingStudents(marks, numberOfStudents) << endl;
        }
        else if (choice == 3) {
            cout << "Good bye " << endl;
        }
        else {
            cout << "Invalid Choice" << endl;
        }

    } while (choice != 3);





    for (int i = 0; i < numberOfStudents; i++)
    {
        delete[] marks[i];
    }

    delete[] marks;
}
