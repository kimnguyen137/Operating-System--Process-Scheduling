// Name: KIM NGUYEN
// PID: 1255456
// COSC 3360
// Section: MON-WED 4:00-5:30PM
// Assignment 1


#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// Struct save all information into Node
struct Node
{
    int clock; // Event time to keep track
    string operation; // Define operation request from text file
    int pid; // process id number
    string status; // process status (arrival/departure) from operations
    int value; // Operation time request in running
    Node *next; // pointer next in linked-list
};
class linkedList
{
private:
    Node *head ; // pointer 
    Node *tail ; // pointer
public:
    linkedList()
    {
        head = nullptr; // linked-list pointer start with null
    }
    // Operations to add new node at the end of linked-list
    void appendNode(string line, int num) // add node to end of list
    {
        Node *newNode = new Node; // node pointer to a new node
        Node *nodeptr = new Node; // node pointer to run through list
        newNode -> operation = line; // add operation information to node
        newNode -> value = num; // add request value information to node
        newNode -> next = NULL; // new node pointer to next is null
       
        // If linked-list is empty make newNode first node.
        if (head == NULL)
        {
            head = newNode; // head and tail become new node   
        }
        // If there is a list, insert newNode at the end.
        else
        {
            nodeptr = head; // append new node to become tail
            while (nodeptr -> next)
                nodeptr = nodeptr -> next;
            nodeptr -> next = newNode;
        }
    }

    // function insert node into eventlist in sorted clock time order
    void insert(int a, string b, int c, string d, int e) 
    {
        Node *newNode; // pointer new node
        Node *Nodeptr; // pointer node pointer
        Node *prevNode; // pointer temporary node
        
        newNode = new Node; // create new node 
        // save struct node information into newNode
        newNode -> clock = a;
        newNode -> operation = b;
        newNode -> pid = c;
        newNode -> status = d;
        newNode -> value = e;

        Nodeptr=head; //
        prevNode=nullptr;
        while( Nodeptr != nullptr && Nodeptr -> clock < a) // traverse through Eventlist to find position to insert node
        {                                             // node inserted in Eventlist sorted in clock time
            prevNode = Nodeptr ;
            Nodeptr = Nodeptr -> next ;
        }
        // If the insert position is to be at the head
        if(prevNode==nullptr)
        {
            newNode -> next = head;
            head = newNode;
        }
        // Else insert Node in to sorted position in Eventlist
        else
        {
            prevNode -> next = newNode;
            newNode -> next = Nodeptr;
        }          
    }

    // function delete node
    void pop()
    {
        if (head ->next == NULL) // if linked-list contain only head, delete head
        {
            delete head; 
            head = NULL;
        }
        else // delete node
        {
            Node *newhead = head -> next;
            delete head;
            head = newhead;
        }
    }

    // function to delete request node of linked-list with corresponding pid
    void popArrivalRequest() 
    {
        Node *nodeptr = head; // pointer at head
        Node *prevnode;
        nodeptr = nodeptr -> next; // traverse list
        prevnode = nodeptr; // link between node
        nodeptr = nodeptr -> next;
        prevnode -> next = nodeptr -> next;
        delete nodeptr; // delete
        
    }
    
    // function to check empty list
    bool is_empty()
    {
        if (head == NULL) return true;
        else return false;
    }

    void displayList() // display linked-list of input 
    {
        Node *nodePtr = head; // new node pointer start at head
        while  (nodePtr != NULL) // traverse through linked-list
        {
            cout << nodePtr -> operation << " ";
            cout << nodePtr -> value << endl;
            nodePtr = nodePtr -> next; // traverse through linked-list
        }
    }
    
    void displayEventList() // display eventlist
    {
        Node* nodePtr = head;
        while(nodePtr!=NULL)
        {
            cout << "(" << nodePtr->clock << ", " << nodePtr->operation << ", " 
            << nodePtr->pid << ", " << nodePtr->status << ", " << nodePtr->value<< ")  ";
            nodePtr = nodePtr->next;
        }
    }
    // function check to return correspoding list instructions of process by pid
    bool checkList(int pid)
    {
        Node* myPtr=head;
        myPtr=myPtr->next;
        if(myPtr->value==pid)
            return true;
        return false;
    }

    // Functions get/return value of the first 3 line of vector of linked list
    // start time, process id, first request instruction
    int arrivalTime() // return start time of process
    {
        return head -> value;
    }
    int arrivalPid() // return process id next after start
    {
        Node *nodeptr = head;
        nodeptr = nodeptr -> next;
        return nodeptr -> value;
    }
    // get request instruction of process, 3rd line
    Node arrivalRequest() // return operation request and its time as node function
    {
        Node mynode;
        Node *nodeptr = head;
        nodeptr=nodeptr->next;
        nodeptr=nodeptr->next;
        if(nodeptr!=NULL)
        {
            mynode.operation = nodeptr->operation;
            mynode.value = nodeptr -> value;
        }
        else
        {
            mynode.operation=" ";
            mynode.value=-1;
        }
        
        return mynode;
    }
    Node getFirstEvent() //
    {
        return *head;
    }
};
// function return list of correspoding process pid, in vector of linked-list
linkedList getListFromVector(vector<linkedList> myVector, int pid)
    {
        linkedList targetList;
        for(int i=0; i<myVector.size(); i++)
        {
            if(myVector[i].checkList(pid)) // same process pid
            {
                targetList=myVector[i]; 
                break;
            }
        }
        return targetList;
    }
// Read text file and store input into vector of linked-list
int NCORES; // Declare number of cores, also equal to number of freecores

// Function to read input file and return into vector of linked-list
vector<linkedList>  readInstruct () 
{
    // Linked-list
    linkedList list;
    // Read text file by I/O redirection, save data into instructions as linked-list
    string word;
    int number;
    int index = -1; //when reach start, index++ to 0 is the first index of vector hold the list of linkedlist
    vector<linkedList> listoflinkedlist;
    // Read first line number of cores, return number of cores into NCORES variable
    cin >> word >> number;
    NCORES = number;
    cout << "__________________________________________________________________________________________________" << endl;
    cout << "__________________________________________________________________________________________________" << endl;
    cout << "__________________________________________________________________________________________________" << endl;
    cout << "Number of cores: " << NCORES << endl<<endl ;
    // Read from second line, store information
    while (cin >> word >> number)
    {
        if (word == "START") // start new process when read string "START"
        {
            linkedList l; //
            l.appendNode(word, number);
            listoflinkedlist.push_back(l);
            index++; // process store in vector start from index 0                      
        }
        else // continue read instructions of process
        {
            listoflinkedlist[index].appendNode(word, number);
        }     
    }
    return listoflinkedlist;
  
}
// Declare
linkedList eventList;

queue <Node> interactivequeue,noninteractivequeue,ssdqueue;

int isinteract ; // Interactive = 1 
                 // Non-Interactive = 0

///////////////////////////
// PROCESS REQUEST ////////
///////////////////////////
int clocktime=0;
int numProcess=0;

// REQUEST CORE
void CoreRequest (int pid, int time, Node myEvent)
{   
    if (NCORES > 0) // check core busy
    {
        NCORES -= 1; // core busy by 1
        int completiontime = clocktime + time;
        eventList.insert (completiontime, "CORE", pid, "departure", 0);
        
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) 
        << "CORE" << setw(18) << time << setw(18) << "RUNNING" << endl;
        
    }
    
    else if (isinteract == 1) // interactive
    {
        interactivequeue.push(myEvent);
        
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) 
        << "CORE" << setw(18) << time << setw(18) << "READY | INTERACTIVE QUEUE" << endl;
    }  
    else if (isinteract == 0) // non-interactive
    {
        
        noninteractivequeue.push(myEvent);
        
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) 
        << "CORE" << setw(18) << time << setw(18) << "READY | NON-INTERACTIVE QUEUE" << endl;
    }  
}
// COMPLETE CORE
void CoreRelease (linkedList myList, int pid)
{
    
    if (!interactivequeue.empty())
    {
        NCORES += 1; // release core by 1
        Node myEvent = noninteractivequeue.front();
        noninteractivequeue.pop();
        
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) << "CORE"  
        << setw(18) << " " << setw(18) << "TERMINATE REQUEST" << endl ;    
        CoreRequest(myEvent.pid, myEvent.value, myEvent);    
    }
    else if (!noninteractivequeue.empty())
    {
        NCORES += 1; // release core by 1
        Node myEvent = noninteractivequeue.front();
        noninteractivequeue.pop();
        
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) << "CORE" 
        << setw(18) << " " << setw(18) << "TERMINATE REQUEST" << endl ;         
        CoreRequest(myEvent.pid, myEvent.value, myEvent);    
    }
    else
    {
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) << "CORE" 
        << setw(18) << " " << setw(18) << "TERMINATE REQUEST" << endl ;   
        NCORES += 1;    
    }
    // GET NEXT REQUEST FROM PROCESS PID
    Node request = myList.arrivalRequest();
    if(request.operation!=" ")
    {
        
        eventList.insert(clocktime,request.operation, pid, "arrival", request.value);       
        myList.popArrivalRequest();
    }
    else
    {
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) << "TERMINATED" << endl;
        numProcess++;

    }  
}

// PROCESS SSD
int ssdQ = 1;
void ssdRequest (int pid, int time, Node myEvent)
{
    if (ssdQ > 0)
    {
        ssdQ -= 1;
        // cout << "ssdQ is: " << ssdQ << endl;
        int completionTime = clocktime + time;
        eventList.insert (completionTime, "SSD", pid, "departure", 0);
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) 
        << "SSD" << setw(18) << time << setw(18) << "BLOCKED" << endl;
    }
    else
    {
        {
            ssdqueue.push(myEvent);
            cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) 
            << "SSD" << setw(18) << time << setw(18) << "BLOCKED | SSD QUEUE" << endl;
        }
    } 
}
void ssdRelease (linkedList myList, int pid)
{
    isinteract = 0;
    if (!ssdqueue.empty())
    {
        ssdQ += 1;
        Node myEvent = ssdqueue.front();
        ssdqueue.pop();
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) << "SSD"  
        << setw(18) << " " << setw(18) << "TERMINATE REQUEST" << endl ;
        ssdRequest(myEvent.pid, myEvent.value, myEvent);
    }
    else 
    {
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) << "SSD" 
        << setw(18) << " " << setw(18) << "TERMINATE REQUEST" << endl ;
        ssdQ += 1;
        
    }
    
    Node request = myList.arrivalRequest();
    
    if (request.operation != " ")
    {
        eventList.insert(clocktime, request.operation, pid, "arrival", request.value);
        myList.popArrivalRequest();
        
    }
    else 
    {
        
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) << "TERMINATED" << endl;
        numProcess++;
    }
 
}

// PROCESS TTY
void userRequest(int pid, int time, Node myEvent)
{
    int completiontime = clocktime + time;
    eventList.insert(completiontime, myEvent.operation, pid, "departure", myEvent.value);
    cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) 
    << "TTY" << setw(18) << time << setw(18) << "BLOCKED" << endl;
}
void userRelease(linkedList myList, int pid)
{
    isinteract = 1;
    Node request = myList.arrivalRequest();
    if (request.operation != " ")
    {
        eventList.insert(clocktime, request.operation, pid, "arrival", request.value);
        myList.popArrivalRequest();
    }
    else 
    {
        cout << left << setw(18) << clocktime << "Process " << setw(18) << pid << setw(18) << "TERMINATED" << endl;
        numProcess++;
    }
}


int main()
{
    vector<linkedList> list =  readInstruct();
    // Get information from vector of linkedlist and insert into eventList
    for (int i=0; i < list.size(); i++)
    {
        int startTime = list[i].arrivalTime();       
        int pid = list[i].arrivalPid();      
        Node anode = list[i].arrivalRequest();    
        eventList.insert(startTime, anode.operation, pid, "arrival", anode.value); 
        list[i].popArrivalRequest();
        // cout << "myList after pop Arrival Request "; list[i].displayList();

    }
    // cout << "EventList: "; eventList.displayEventList();

    int numSSD=0, numTTY=0;
    int coreTime=0;
    int ssdTime=0;
    Node firstEvent; // process first event, pop event from list
    
    // run request from eventlist, if empty function end and terminate
    while (!eventList.is_empty())
    {
        firstEvent = eventList.getFirstEvent();
        eventList.pop();
        clocktime=firstEvent.clock;
        // If next event in Eventlist is CORE
        if (firstEvent.operation == "CORE" && firstEvent.status == "arrival")
        {
            coreTime += firstEvent.value;
            CoreRequest(firstEvent.pid,firstEvent.value, firstEvent);
            // cout <<endl<<endl<< "EventList: "; eventList.displayEventList(); cout << endl ;
        }
        else if (firstEvent.operation == "CORE" && firstEvent.status == "departure")
        {
            linkedList myList = getListFromVector(list, firstEvent.pid);
            CoreRelease(myList, firstEvent.pid);
            // cout << "EventList: "; eventList.displayEventList(); cout << endl ;            
        }
        // If next event in Eventlist is SSD
        else if (firstEvent.operation == "SSD" && firstEvent.status == "arrival")
        {
            numSSD++;
            ssdTime += firstEvent.value;
            ssdRequest(firstEvent.pid, firstEvent.value, firstEvent);
            // cout << endl<<endl << "Eventlist: "; eventList.displayEventList(); cout << endl;
        }
        else if (firstEvent.operation == "SSD" && firstEvent.status == "departure")
        {
            linkedList myList = getListFromVector(list, firstEvent.pid);
            ssdRelease(myList, firstEvent.pid);
            
            // cout << "EventList: "; eventList.displayEventList(); cout << endl;
        }
        // If next event in Eventlist is TTY
        else if (firstEvent.operation == "TTY" && firstEvent.status == "arrival")
        {
            numTTY++;
            userRequest(firstEvent.pid, firstEvent.value, firstEvent);
            // cout << endl<<endl << "Eventlist: "; eventList.displayEventList(); cout << endl;
        }
        else if (firstEvent.operation == "TTY" && firstEvent.status == "departure")
        {
            linkedList myList = getListFromVector(list, firstEvent.pid);
            ssdRelease (myList, firstEvent.pid);
            // cout << "EventList: "; eventList.displayEventList(); cout << endl;
        } 
    }
    cout << "------------------SUMMARY------------------" << endl;
    
    cout << "Total elapsed time: " << clocktime << " ms " << endl;
    cout << "Number of processes that completed: " << numProcess << endl;
    cout << "Total number of SSD accesses: " << numSSD << endl;
    // cout << "Total number of TTY interactions = " << numTTY << endl;
    double coreAverage = (double)coreTime / (double)clocktime;
    cout << "Average number of busy core: " << fixed << setprecision(3) << coreAverage << endl;
    double ssdUtilization = (double)ssdTime / (double)clocktime;
    cout << "SSD utilization: " << fixed << setprecision(3) << ssdUtilization << endl;

    return 0;
}

