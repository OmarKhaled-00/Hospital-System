#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include "STD_TYPES.h"

/* Function declarations */
struct Person {
    char ID[8]; /* ID can hold up to 7 characters plus the null terminator */
    char password[10]; /* Assuming a password of maximum 10 characters */
    uint8 userType[5]; /* User type (USR, DOC, ITAD) plus null terminator */
};
struct HI{
    uint8 Name[30],Gender[10];
    uint32 Age;
       
}RESERVATION_Info[100];
struct OP {
    uint8 His_Name[30], His_Gender[10], Disease[30], Address[30], Doctor_Name[30], Telephone[20];
    uint8 His_Age;
    
} OPERATION_INFO[100];

uint8 counterC = 0, Local_Pointers[4] = {0},numberOfPatient,counter;
f32 Time[11];
f32 Appointment[11];

const struct Person people[40]; /* Array to hold 40 people's information (20 users + 20 doctors) */

uint32 customRand(uint32 *seed); /* Custom pseudo-random number generator */
char getRandomChar(const char *charset, int length, uint32 *seed); /* Function to generate a random character from a given set of characters */
void generateRandomPerson(struct Person *person, uint8 *userType, uint16 *counter); /* Function to generate a random ID and password for a person */
void ACCESS_PERMATION(void); /* Function to generate unique IDs and passwords for users and doctors */
bool verifyUserLogin(const char* enteredID, const char* enteredPassword, const struct Person people[], uint16 numPeople); /* Function to verify login credentials for a user */
bool verifyDoctorLogin(const char* enteredID, const char* enteredPassword, const struct Person people[], uint16 numPeople); /* Function to verify login credentials for a doctor */
bool verifyITAdminLogin(const char* enteredID, const char* enteredPassword); /* Function to verify login credentials for an IT administrator */
void LoginPage(void); /*Function to represent Login page*/
void ITadmin_page(void);/*Function to represent ITadmin page*/
void User_page(void);/*Function to represent User_page*/
void Doctor_page(void);/*Function to represent Doctor_page*/
void Admin_Mode(void);/*Function to allow reptionist to regiter the patient*/
void Patient_Info(void);/*Function to view the patients info*/
void FirstGate(void);/*Function to ask user which mode is prefered to use*/
void Add(void);/*Function to add informations about patient*/
void Edit(void);/*Function to edit informations about patient */
void Cancel(void);/*Function to cancel informations about patient */
void View(void);/*Function to view informations about patient */
void Verfication(void);/*Function to verify the login */
void App(void);/*Application*/
void Detect_Malware(void);/*Function to detect abnormal behavior*/
void printPatientInfo(int index);/*Function to view informations about patient */
void printRoomReservation(const char *roomName, int index);/*Function to view informations about Operation Rooms */
void Operations_Rooms();/*Structure of Operation Room*/
void CheckDoctorOperation(const char *doctorName);/*Function to check the name of operation and time for every doctor */
void Doctor_Mode(void);/*Doctor Page */
void Fake_Page(void);/*Cyber Attack Page*/
int check_ip_hostname(const char *desired_ip, const char *desired_hostname);/*Checking Ip Address*/
volatile static uint8 u8GetPassLock=0;
static char enteredID[8];
static char enteredPassword[10];
static uint8 Login_Counter=0u;
bool continueLogin = true;
const char *desired_ip = "";       // Replace with the desired IP address
const char *desired_hostname = "";  // Replace with the desired hostname



int main()
{
    App();
    return 0;
}

int check_ip_hostname(const char *desired_ip, const char *desired_hostname) {
    WSADATA wsaData;
    char hostbuffer[256];
    struct hostent *host_entry;
    char *IPbuffer;
    

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
       
    }

    // Get the hostname
    if (gethostname(hostbuffer, sizeof(hostbuffer)) == SOCKET_ERROR) {
        printf("gethostname failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        
    }

    // Get host information
    host_entry = gethostbyname(hostbuffer);
    if (host_entry == NULL) {
        printf("gethostbyname failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        
    }

    // Convert the IP address to a string
    IPbuffer = inet_ntoa(*(struct in_addr *)*host_entry->h_addr_list);

   // printf("Current Hostname: %s\n", hostbuffer);
    //printf("Current IP Address: %s\n", IPbuffer);

    // Check if the desired IP and hostname match the current ones
    if (strcmp(IPbuffer, desired_ip) == 0 && strcmp(hostbuffer, desired_hostname) == 0) {
        u8GetPassLock = 1; /*Ip Address is verified */
    } else {
        u8GetPassLock = 3; /*Ip Address isn't verified*/
    }

    // Cleanup Winsock
    WSACleanup();

   
}
/* Custom pseudo-random number generator */
uint32 customRand(uint32 *seed) {
    *seed = (*seed * 1103515245 + 12345) & 0xFFFFFFFF;
    return (*seed >> 16) & 0x7FFF;
}

/* Function to generate a random character from a given set of characters */
char getRandomChar(const char *charset, int length, uint32 *seed) {
    return charset[customRand(seed) % length];
}

/* Function to generate a random ID and password for a person */
void generateRandomPerson(struct Person *person, uint8 *userType, uint16 *counter) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_-+=";
    const int charsetLength = sizeof(charset) - 1; /* Length of the charset excluding the null terminator */
    uint32 seed = rand(); /* Seed for the custom random number generator */

    /* Set user type */
    strcpy((char *)person->userType, (char *)userType);

    /* Generate random ID */
    sprintf(person->ID, "%s%03d", (char *)userType, (*counter)++);

    /* Generate random password */
    for (int j = 0; j < 6; j++) { /* Generate 6-character password */
        person->password[j] = getRandomChar(charset, charsetLength, &seed);
    }
    person->password[6] = '\0'; /* Null terminate the password string */
}

/* Function to generate unique IDs and passwords for users and doctors without parameters */
void ACCESS_PERMATION() {
    uint16 counter = 1; /* Counter for generating unique IDs */

    /* Generate unique IDs and passwords for users and doctors */
    for (int i = 0; i < 20; i++) {
        generateRandomPerson((struct Person *)&people[i], (uint8 *)"USR", &counter); /* Generate for users */
    }
    for (int i = 20; i < 40; i++) {
        generateRandomPerson((struct Person *)&people[i], (uint8 *)"DOC", &counter); /* Generate for doctors */
    }

    /* Print the generated IDs and passwords within a square frame */
    printf("+------------------------+----------------------+----------------------+\n");
    printf("| ID                     | Password             | User Type            |\n");
    printf("+------------------------+----------------------+----------------------+\n");

    for (int i = 0; i < 40; i++) {
        printf("| %-24s | %-20s | %-20s |\n", people[i].ID, people[i].password, (char *)people[i].userType);
        if ((i + 1) % 10 == 0 && i != 39) {  // Start a new row after every 10 entries, except the last row
            printf("+------------------------+----------------------+----------------------+\n");
            printf("| ID                     | Password             | User Type            |\n");
            printf("+------------------------+----------------------+----------------------+\n");
        }
    }

    printf("+------------------------+----------------------+----------------------+\n");
}


/* Function to verify login credentials for a user */
bool verifyUserLogin(const char* enteredID, const char* enteredPassword, const struct Person people[], uint16 numPeople) {
    /* Check if entered ID and password match any user in the array */
    for (int i = 0; i < numPeople; i++) {
        if (strcmp(enteredID, people[i].ID) == 0 && strcmp(enteredPassword, people[i].password) == 0 && strcmp((char *)people[i].userType, "USR") == 0) {
            return true; /* Login successful for user */
        }
    }
    return false; /* Login failed */
}

/* Function to verify login credentials for a doctor */
bool verifyDoctorLogin(const char* enteredID, const char* enteredPassword, const struct Person people[], uint16 numPeople) {
    /* Check if entered ID and password match any doctor in the array */
    for (int i = 0; i < numPeople; i++) {
        if (strcmp(enteredID, people[i].ID) == 0 && strcmp(enteredPassword, people[i].password) == 0 && strcmp((char *)people[i].userType, "DOC") == 0) {
            return true; /* Login successful for doctor */
        }
    }
    return false; /* Login failed */
}

/* Function to verify login credentials for an IT administrator */
bool verifyITAdminLogin(const char* enteredID, const char* enteredPassword) {
    /* Simulated hardcoded IT administrator ID and password */
    const uint8 adminID[] = "ITAD001";
    const uint8 adminPass[] = "admin123";

    /* Verify entered ID and password */
    if (strcmp((char *)enteredID, (char *)adminID) == 0 && strcmp((char *)enteredPassword, (char *)adminPass) == 0) {
        return true; /* Login successful */
    } else {
        return false; /* Login failed */
    }
}
void LoginPage(void) /*Function to represent Login page*/
{
    printf("             ****************************\n");
    printf("             **** RESERVATION_SYSTEM ****\n");
    printf("             ****************************\n");
    printf("\n\n");
    printf("                                                                Hospital_Reservation_Secured_Sytsem");
    printf("\n");
    printf("                                                                *Developed by Eng: Omar Khaled Abd elmoez*");
    printf("\n");
    printf("                                                                Version2.0");
    printf("\n");
    printf("                                     Contact_Info : (LinkedIn):https://www.linkedin.com/in/omar-khaled-4a85aa271/");
    printf("\n");
    printf("                                                                <<Your care and privacy are important to us>>");
    printf("\n\n");
    printf("                     LOGIN");
    printf("\n");
    


}

void FirstGate(void)
{
    static uint8 check=0u;
    printf("                                     1)Admin_Mode\n");
    printf("                                     2)Patient_Info\n");
    printf("                                     3)Exit\n");
    printf("                                      Answer: ");
    if(scanf("%d",&check))
    {
        /*Do Nothing , Continue*/
    }
    else
    {
        printf("                                       Invalid_Input, Try Again. \n");
        printf("                                     1)Admin_Mode\n");
        printf("                                     2)Patient_Info\n");
        printf("                                     3)Exit\n");
        printf("                                      Answer: ");
        if(scanf("%d",&check))
        {
            /*Do Nothing , Continue*/
        }
        else
        {
            printf("                                     Time is out..\n");
            exit(0);
        }

    }
    switch (check)
    {
    case(1):
    Admin_Mode();
    break;
    case(2):
    Patient_Info();
    break;
    case(3):
    exit(0);
    break;    
    default:
    break;
    }
}

void Fake_Page(void)
{

    printf("             ******************************\n");
    printf("             **** RESERVATION_SYSTEM ****\n");
    printf("             ****************************\n");
    printf("\n\n");
    printf("                                                                Hospital_Reservation_Secured_Sytsem");
    printf("\n");
    printf("                                                                *Developed by Eng: Omar Khaled Abd elmoez*");
    printf("\n");
    printf("                                                                Version2.0");
    printf("\n");
    printf("                                     Contact_Info : (LinkedIn):https://www.linkedin.com/in/omar-khaled-4a85aa271/");
    printf("\n");
    printf("                                                                <<Your care and privacy are important to us>>");
    printf("\n\n");
    printf("                     LOGIN");
    printf("\n");
}
void Patient_Info(void)
{
    uint8 check;
    system("cls");
    printf("             *******************************\n");
    printf("             ********* Patient_Info*********\n");
    printf("             *******************************\n");
    printf("\n\n");
    printf("**Enter your choice**\n1.View patient record\n2.View today is reservation\n3.Exit\n");
    printf("Answer:");
     if(scanf("%d",&check))
    {
        /*Do nothing , Continue*/
    }
    else
    {
        printf("Invalid_Input,Try Agian..\n");
        printf("**Enter your choice**\n1.View patient record\n2.View today is reservation\n3.Exit\n");
        if(scanf("%d",&check))
        {
            /*Do nothing , Continue*/

        }
        else
        {
            printf("Time is out..\n");
            system("cls");
            exit(0);
        }
    }
    if(check==1)
        {
             uint32 ID;
            printf("Enter the ID for patient((0) realted to first person): ");
             if(scanf("%d",&ID))
            {
                /*Do nothing , Continue*/
            }
           else
            {
                printf("Invalid_Input,Try Agian..\n");
                printf("Enter the ID for patient((0) realted to first person): ");
                if(scanf("%d",&ID))
                {
                    /*Do nothing , Continue*/

                }
                else
                {
                    printf("Time is out..\n");
                    system("cls");
                    exit(0);
                }
            }
            printf("Name = ");
            puts(RESERVATION_Info[ID].Name);
            printf("gender = ");
            puts(RESERVATION_Info[ID].Gender);
            printf("\nAge=%d\n",RESERVATION_Info[ID].Age);
            printf("the reserved slot %.2f\n",Appointment[ID]);
            printf("\n");
            sleep(5);
           
           
        }
        else if(check == 2)
        {
            for(uint32 i =0; i<=numberOfPatient; i++)
            {
                  
            printf("Name = ");
            puts(RESERVATION_Info[i].Name);
            printf("gender = ");
            puts(RESERVATION_Info[i].Gender);
            printf("\nAge=%d\n",RESERVATION_Info[i].Age);
            printf("the reserved slot %.2f\n",Appointment[i]);
            printf("\n");
                
            }
            sleep(5);
            
            
           
        }
        else
        {
            system("cls");
            main();
        }
    Patient_Info();

}
void Admin_Mode(void)
{
    static uint8 choice;
     system("cls");
        printf("             ****************************\n");
        printf("             ********* Admin_Mode********\n");
        printf("             ****************************\n");
        printf("\n\n");

         printf("**Enter your choice**\n\n1)ADD information\n2)EDIT information\n3)Back to user mode\n4)Cansel reservation\n5)Operations_Rooms\n6)Exit \noption=");
        if(scanf("%d",&choice))
        {

        }
        else
        {
            printf("Invalid_Input, Try Again..\n");
            system("cls");
            printf("**Enter your choice**\n\n1)ADD information\n2)EDIT information\n3)Back to Patinet_info\n4)Cansel reservation\n5)Operations_Rooms EXIT\n6)EXIT\n option=");
               if(scanf("%d",&choice))
              {
                /*do nothing continue*/
              }
              else
              {
                printf("Time is out..\n");
                exit(0);
              }
        }
        fflush(stdin);
        while(choice!=6)  
        {
          if(choice==1)/*add*/
        {
            system("cls");
            Add();
            
        }
        else if(choice==2)/*edit*/
        {
            system("cls");
            Edit();
            
        }
       
        else if(choice==3)/*user_mode*/
        {
            system("cls");
            Patient_Info();
            
        }
        else if(choice==4)/*cancel*/
        {
            system("cls");
            Cancel();
            
        }
        else if(choice==5) /*Operation Rooms*/
        {
          system("cls");  
          Operations_Rooms();
            
        }
        else if(choice==6)/*Exit*/
        {
            exit(0);
        }
        else
        {
            system("cls");
            printf("\n\nInvalid input , Try again by using valid inputs");
        }
        printf("\n\n");
        }

}

void Add()/*Function to add informations about patient*/
{
    uint32 numberOfPatient;
  system("cls");
    printf("             ****************************\n");
    printf("             ****** ADD_INFORMATION******\n");
    printf("             ****************************\n");
    printf("\n\n");
    printf("Data inputed in data base= %d\n\n",counter);
    printf("How many Patients do you want to record: ");
    if(scanf("%d",&numberOfPatient))
    {
        /*Do nothing , Continue*/
    }
    else
    {
        printf("Invalid_Input,Try Agian..\n");
        printf("How many Patients do you want to record:");
        if(scanf("%d",&numberOfPatient))
        {
            /*Do nothing , Continue*/

        }
        else
        {
            printf("Time is out..\n");
            system("cls");
            exit(0);
        }
    }
     uint8 j , sum;
      sum =numberOfPatient+counter;
   
         for(uint8 i=counter, j=0; i< sum; i++)
        {
             printf("\n");
             fflush(stdin);
             printf("Enter the name of the patient : ");
             gets(RESERVATION_Info[i].Name);
             fflush(stdin);
             printf("Enter the age of the patient : ");
             fflush(stdin);
             if(scanf("%d",&RESERVATION_Info[i].Age))
             {

             }
             else
             {
                printf("Invalid_Input,Try Again: ");
                fflush(stdin);
                if(scanf("%d",&RESERVATION_Info[i].Age))
                {

                }
                else
                {
                    printf("Invalid_Input, Back To The List..\n");
                    system("cls");
                    Add();
                }

             }
             fflush(stdin);
             printf("Enter the gender of the patient : ");
             gets(RESERVATION_Info[i].Gender);
             fflush(stdin);
             printf("Enter your desired appointment of (from 12.30 to 5.30 every appointment takes half hour)\n");
             scanf("%f",&Appointment[i]);
             fflush(stdin);

               j++;
              counter++;
        }

    system("cls");
    main();
    
}
void Edit()/*Function to edit informations about patient */
{
   uint32 q,p,num=0;
    fflush(stdin);
    printf("What do you want to edit ?\n");
    printf("Enter your option\n");
    printf("1.Name\n2.gender\n3.Age\n\n4.Appointment\n5.exit.\n");
    printf("Option=");
     if(scanf("%d",&q))
    {
        /*Do Nothing , Continue*/
    }
    else
    {
        printf("Invalid_Input, Try Again. ");
        printf("1.Name\n2.gender\n3.Age\n4.exit.\n");
        printf("Option: ");
        if(scanf("%d",&q))
        {
            /*Do Nothing , Continue*/
        }
        else
        {
            printf("Time is out..\n");
            exit(0);
        }
    }
     printf("Enter the serial no of that patient= (0 - %d)=",num);
        scanf("%d",&p);/*serial number*/
        if(p<=num)
        {
            if(q==1)
            {
                fflush(stdin);
                printf("Enter the new name=");
                gets(RESERVATION_Info[p].Name);
                

            }
            else if(q==2)
            {
                fflush(stdin);
                printf("Enter the new gender=");
                gets(RESERVATION_Info[p].Gender);
            }
            else if(q==3)
            {
                fflush(stdin);
                printf("Enter the new Age=");
                if(scanf("%d",&RESERVATION_Info[p].Age))
                {

                }
                else
                {
                    printf("Invalid_Input,TryAgain..");
                    printf("Enter The Age: ");
                    if(scanf("%d",&RESERVATION_Info[p].Age))
                    {

                    }
                    else
                    {
                        printf("Timed out...");
                        system("cls");
                        exit(0);
                    }
                }
            }

            else if(q==4)
            {
                fflush(stdin);
               printf("Enter the new appointment: ");
               scanf("%f",&Appointment[p]);
            }
            else if(q==5)
            {
                Admin_Mode();
            }
        }
        else
        {
            printf("\n\nInvalid Serial \nTry Again !!\n\n");
            exit(0);
        }
}
void Cancel()/*Function to cancel informations about patient */
{
  uint32 num,f,h;
    printf("Enter the indetification of the patient you want to delete= \n");
    scanf(" %d",&f);
    printf("What do you want ?\n");
    printf("1.Remove the whole record\n2.Remove Name\n3.Remove gender\n4.Remove age\n5.Reservation\nOption = ");
    scanf("%d",&h);
        if(h==1)
        {
            if(f<num)
            {
                strcpy(RESERVATION_Info[f].Name,RESERVATION_Info[f+1].Name);
                RESERVATION_Info[f].Age=RESERVATION_Info[f+1].Age;
                strcpy(RESERVATION_Info[f].Gender,RESERVATION_Info[f+1].Gender);
                Appointment[f]=0;
                printf("stuff removed \n");
                f++;
            }
            main();
            num--;
        }
        else if(h==2)
        {
            strcpy(RESERVATION_Info[f].Name,"Cleared");
            main();
        }
        else if(h==3)
        {
            strcpy(RESERVATION_Info[f].Gender,"Cleared");
            main();
        }
        else if(h==4)
        {
            RESERVATION_Info[f].Age=0;
            main();
        }
        else if(h==5)
        {
            Appointment[f]=0;
            main();
        }
        else
        {
            printf("invalid input , please try again: \n");
        }
        main();
}
void View()/*Function to view informations about patient */
{
  uint8 x=0;
}
void Verfication()
{
    if(u8GetPassLock ==3)
    {
          Fake_Page();
           // Prompt for IT administrator login
        printf("              Enter ID: ");
        scanf("%s", enteredID);
        printf("              Enter Password: ");
        scanf("%s", enteredPassword);


        printf("Login is successfully done , please wait...");
        sleep(10);
    }
    else if(u8GetPassLock == 1)
    {
           
      while ((continueLogin) && (Login_Counter!=3))
      {
         LoginPage();
        // Prompt for IT administrator login
        printf("              Enter ID: ");
        scanf("%s", enteredID);
        printf("              Enter Password: ");
        scanf("%s", enteredPassword);

        // Check user type and verify login accordingly
        if (enteredID[0] == 'U' && enteredID[1] == 'S' && enteredID[2] == 'R') {
            bool userLogin = verifyUserLogin(enteredID, enteredPassword, people, 40);
            if (userLogin) {
                printf("User login successful.\n");
                sleep(2);
                system("cls");
                FirstGate();
            } else {
                printf("User login failed.\n");
                Login_Counter++;
            }
        } else if (enteredID[0] == 'D' && enteredID[1] == 'O' && enteredID[2] == 'C') {
            bool doctorLogin = verifyDoctorLogin(enteredID, enteredPassword, people, 40);
            if (doctorLogin) {
                printf("Doctor login successful.\n");
                system("cls");
                Doctor_Mode();
            } else {
                printf("Doctor login failed.\n");
                Login_Counter++;
            }
        } else if (strcmp((char *)enteredID, "ITAD001") == 0) {
            bool adminLogin = verifyITAdminLogin(enteredID, enteredPassword);
            if (adminLogin) {
                system("cls");
                printf("IT administrator login successful.\n");

                // Call UIP function to generate IDs and passwords
                ACCESS_PERMATION();
            } else {
                printf("IT administrator login failed.\n");
                Login_Counter++;
            }
        } else {
            printf("Invalid ID.\n");
            Login_Counter++;
        }
        if(Login_Counter == 3)
        {
            system("cls");
            printf("Alarm security is on, no one can enter the server until IT_adminsterator checking malware");
            sleep(15);
            system("cls");
            printf("                                      Webpage IT Adminsterator");
            Detect_Malware();
            
            Login_Counter=0;
        }
        else
        {
            /*Do nothing , continue*/
        }

        // Ask if the user wants to log in again
        char choice;
        printf("Do you want to log in again? (Y/N): ");
        scanf(" %c", &choice);
        if (choice != 'Y' && choice != 'y') {
            continueLogin = false; // Exit the loop
        }
        else{
            system("cls");
            Verfication();
        }
                
      }
    }
    
}


void printPatientInfo(int index) {
    printf("The patient's name: %s\n", OPERATION_INFO[index].His_Name);
    printf("His age: %d\n", OPERATION_INFO[index].His_Age);
    printf("His gender: %s\n", OPERATION_INFO[index].His_Gender);
    printf("His address: %s\n", OPERATION_INFO[index].Address);
    printf("His telephone: %s\n", OPERATION_INFO[index].Telephone);
    printf("The name of the operation: %s\n", OPERATION_INFO[index].Disease);
    printf("The name of the doctor: %s\n", OPERATION_INFO[index].Doctor_Name);
    printf("The appointement of the operations: %.2f",Time[index]);
}

void printRoomReservation(const char *roomName, int index) {
    printf("*****************************************\n");
    printf("***********  %s ROOM   ***********\n", roomName);
    printf("*****is successfully reserved*****\n");
    printPatientInfo(index);
    printf("\n");
    printf("*****************************************\n");
}

void Operations_Rooms() {
    system("cls");
    printf("             **********************************\n");
    printf("             ********* Operations_Rooms********\n");
    printf("             **********************************\n\n");

    char ch;
    printf("Do you want to reserve an operation room or view available rooms? (R or V) ");
    printf("Answer:");
    scanf(" %c", &ch);
    if (ch == 'R') {
        if (counterC < 4) {
            char roomName[4];
            snprintf(roomName, sizeof(roomName), "A%d", counterC + 1);

            printf("Enter the full name of the patient: ");
            fflush(stdin);
            gets(OPERATION_INFO[counterC].His_Name);
            printf("Enter the age of the patient: ");
            scanf("%d", &OPERATION_INFO[counterC].His_Age);
            printf("Enter the gender of the patient: ");
            fflush(stdin);
            gets(OPERATION_INFO[counterC].His_Gender);
            printf("Enter the name of operation: ");
            fflush(stdin);
            gets(OPERATION_INFO[counterC].Disease);
            printf("Enter telephone number: ");
            fflush(stdin);
            gets(OPERATION_INFO[counterC].Telephone);
            printf("Enter His address: ");
            fflush(stdin);
            gets(OPERATION_INFO[counterC].Address);
            printf("Enter Doctor's name: ");
            fflush(stdin);
            gets(OPERATION_INFO[counterC].Doctor_Name);
            printf("Enter the appointement of the operation: ");
            fflush(stdin);
            scanf("%f",&Time[counterC]);

            Local_Pointers[counterC] = 1;
            counterC++;

            printRoomReservation(roomName, counterC - 1);
        } else {
            printf("All operation rooms are reserved.\n");
        }
    } else if (ch == 'V') {
        if (counterC == 0) {
            printf("There is no reservation.\n");
        } else {
            for (int i = 0; i < 4; i++) {
                if (Local_Pointers[i] == 1) {
                    char roomName[4];
                    snprintf(roomName, sizeof(roomName), "A%d", i + 1);
                    printRoomReservation(roomName, i);
                }
            }
        }
    }

    sleep(5);
    system("cls");
    main(); // Assuming main function exists
}


void CheckDoctorOperation(const char *doctorName) {
    bool found = false;
    for (int i = 0; i < counterC; i++) {
        if (strcmp(OPERATION_INFO[i].Doctor_Name, doctorName) == 0) {
            found = true;
            printf("Doctor's Name: %s\n", OPERATION_INFO[i].Doctor_Name);
            printf("Patient's Name: %s\n", OPERATION_INFO[i].His_Name);
            printf("Operation: %s\n", OPERATION_INFO[i].Disease);
            printf("Age:%d\n",OPERATION_INFO[i].His_Age);
            printf("Time: %.2f\n", Time[i]);
            printf("\n");
        }
    }
    if (!found) {
        printf("Doctor '%s' not found or doesn't have an operation today.\n", doctorName);
    }
}
void Doctor_Mode(void) {
    // Your existing code here...

    // Example usage of CheckDoctorOperation
    char doctorName[30];
    printf("Enter the doctor's name to check operations: ");
    fflush(stdin);
    gets(doctorName);
    CheckDoctorOperation(doctorName);

    // Your existing code here...
}
void Detect_Malware(void)/*Function to detect abnormal behavior*/
{
    char c;
    system("cls");
    printf("Checking Malware....\n");
    sleep(5);
    printf("Processing....\n");
    sleep(5);
    printf("Dectection the IP address....\n");
    sleep(2);
    printf("Operation is successfully checked our server.\n");
    printf("There is someone wants to enter our server.\n");
    printf("Blocking IP address?");
    printf("Answer:");
    scanf(" %c",&c);
    
    printf("Answer:");
    if(c == 'y')
    {
         char t;
        printf("Blocking....");
        sleep(1);
        printf("Successfully Blocked.");
        printf("Accessing Users?");
        scanf(" %c",&t);
       
        if(t == 'y')
        {
            Verfication();
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        ACCESS_PERMATION();
    }
}

void App()
{
    check_ip_hostname(desired_ip, desired_hostname);
    Verfication();
}

