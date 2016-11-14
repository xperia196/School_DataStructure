#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

template<class TYPE>
struct  NODE{
 TYPE data;
 NODE  *link;
};	//노드를 선언합니다.

template<class TYPE, class KTYPE>
class List{
     private:
       NODE<TYPE> *head;
       NODE<TYPE> *pos;
       NODE<TYPE> *rear;
       int count;
    
    bool _add(NODE<TYPE> *pPre, TYPE dataIn);	//사용자를 추가하는 함수 선언
    void _delete (NODE<TYPE> *pPre, NODE<TYPE> *pLoc, TYPE *dataOutPtr);	//사용자를 제거하는 함수 선언
    bool _search (NODE<TYPE> **pPre, NODE<TYPE> **pLoc, KTYPE identify, int& numder);	//사용자를 검색하는 함수 선언
	
  public:
   List(void);
   ~List(void);
   int addNode(TYPE dataIn, int& numder);
   bool removeNode(KTYPE identify, TYPE *dataOutPtr);
   bool searchNode(KTYPE identify, TYPE& dataOut, int& numder);
};	//리스트를 호환하는 List 클래스를 선언합니다.

template<class TYPE, class KTYPE>
List<TYPE, KTYPE> :: List(void){
 head = NULL;
 pos = NULL;
 rear = NULL;
 count = 0;
}	//List에서 포매팅을 할 수 있도록 합니다.

template<class TYPE, class KTYPE>
int List<TYPE, KTYPE> :: addNode(TYPE dataIn, int& numder){

 bool found;
 bool success;
 
 NODE<TYPE> *pPre;
 NODE<TYPE> *pLoc;
 
 found = _search(&pPre, &pLoc, dataIn.identify, numder);
 if(found)
  return(+1);	//키가 중복되었다면 +1을 리턴합니다.
 success = _add(pPre, dataIn);
 if(!success)
  return(-1);	//데이터의 오버플로우(Overflow)가 발생하면 -1을 리턴합니다.
 return(0);
} // 노드 추가 템플릿 정의

template<class TYPE, class KTYPE>
bool List<TYPE, KTYPE> :: _add(NODE<TYPE> *pPre, TYPE dataIn){

 NODE<TYPE> *pNew;

 if(!(pNew = new NODE<TYPE>))
  return false;	//추가할 노드가 이미 정의화되어있으면 false를 반환합니다.
 pNew->data = dataIn;
 pNew->link = NULL;
 if(pPre == NULL)
 {
  pNew->link = head;
  head = pNew;
 }	//pPre가 없으면 첫 노드의 앞이나 빈 리스트에 삽입합니다.
 else
 {
  pNew->link = pPre->link;
  pPre->link = pNew;
 }	//pPre의 존재 하에 중간, 또는 끝에 삽입합니다.
 if(pNew->link == NULL)
  rear = pNew;	//리스트의 마지막에 삽입되어 있으면 빈 리스트에 삽입합니다.
 count++;
 return true;
}

template<class TYPE, class KTYPE>
bool List<TYPE, KTYPE> :: removeNode(KTYPE dltId, TYPE *pDataOut){
 bool found;
 NODE<TYPE> *pPre;
 NODE<TYPE> *pLoc;
 int numder = 0;
 found = _search(&pPre, &pLoc, dltId, numder);
 if(found)
  _delete(pPre, pLoc, pDataOut);	//노드가 발견되었다면, 그것을 삭제합니다.
 return found;
}	//노드 제거 템플릿 정의

template <class TYPE, class KTYPE>
void List<TYPE, KTYPE> :: _delete(NODE<TYPE> *pPre, NODE<TYPE> *pLoc, TYPE *pDataOut){
 *pDataOut = pLoc->data;
 if(pPre == NULL)
  head = pLoc->link;
 else
  pPre->link = pLoc->link;
 if(pLoc->link == NULL)
  rear = pPre;
 count--;	//파일 줄의 수 하나 줄이기
 delete pLoc;	//메모리 반환
 return;
}

template<class TYPE, class KTYPE>
bool List<TYPE, KTYPE> :: searchNode(KTYPE identify, TYPE& dataOut, int& numder){
 bool found;
 NODE<TYPE> *pPre;
 NODE<TYPE> *pLoc;

 found = _search(&pPre, &pLoc, identify, numder);

 if(found)
  dataOut = pLoc->data;	
	//노드를 찾았다면, dataOut는 찾은 데이터를 가지게 됩니다.
 return found;
}	//노드 찾기 템플릿 정의

template<class TYPE, class KTYPE>
bool List<TYPE, KTYPE> :: _search (NODE<TYPE> **pPre, NODE<TYPE> **pLoc, KTYPE identify, int& numder){
 *pPre = NULL;
 *pLoc = head;
 if(count == 0)
  return false;

 if(strcmp(identify, rear->data.identify) > 0)
 {
  *pPre = rear;
  *pLoc = NULL;
  numder = 1;
  return false;
 }

 while(strcmp(identify, (*pLoc)->data.identify) > 0)
 {
  *pPre = *pLoc;
  *pLoc = (*pLoc)->link;
  numder++;
 }	//파일을 한번씩 둘러볼때 까지 찾기 시도

 if(strcmp(identify, (*pLoc)->data.identify) == 0)
  return true; //찾기에 성공했으면 true 반환
 else
  return false;	//그게 아니면(찾기에 실패했으면) false 반환
}

template<class TYPE, class KTYPE>
List<TYPE, KTYPE> :: ~List(void){
 NODE<TYPE> *deletePtr;

 if(head)
 {
  while(count > 0){
   deletePtr = head;
   head = head->link;
   count--;
   delete deletePtr;
  }
 }
}	//리스트를 제거하고, 메모리를 반환하여 효율적으로 리소스 활용

struct PICTURE{
 char identify[15];	//사용자 ID에 관여한 변수
 char info[140];	//사용자의 기타 정보에 관여한 변수
};

void instr (void);
void search (List <PICTURE,char*>&list);
void printList (List <PICTURE,char*>&list);
void process (List <PICTURE,char*>&list);
char getChoice (void);
void init (List <PICTURE,char*>&list);
void addnode(List <PICTURE,char*>&list);
void deletenode(List <PICTURE,char*>&list);

int main(void){
 List<PICTURE,char*>list;
 init (list);
 process (list);

 cout <<"\nGoodbye. Program halting..\n";
 return 0;	//모든 하위작업들이 함수들로 이루어져 있으므로 마지막(process)에서 끝내는 순간 프로그램을 종료합니다.
}

void init(List <PICTURE, char*>& list){
 ifstream fileIO;
 int addResult;
 PICTURE pic;
 int user = 0, count = 0, numder = 0;

 fileIO.open("passwd"); //파일을 여세요.
 if(!fileIO){   
  cerr<<"\a We can't Open the file. Halting.. \n";
  exit(110);	//파일이 없다면 오류메시지를 표시하고, 프로그램을 강제 종료합니다.
 }

 cout << "Organizing User Table\n"
  << "Reading file and establishing Table\n";
 
 while(!fileIO.eof()){
  fileIO.getline(pic.identify, sizeof(pic.identify), ':');
  fileIO.getline(pic.info, sizeof(pic.info));
  user += 1;	//':'을 분기로 파일의 한 행씩 파일을 계속 읽습니다.
  addResult =list.addNode(pic, numder);
  count++;	//1줄을 읽어들일때마다 count를 1씩 증가합니다.

  if(addResult != 0){
   if(addResult == -1){
    cout<<"Memory Overflow. Halting..\n";
    exit(120);
   }	//메모리가 오버플로우 될 경우, 오류메시지를 표시하고 프로그램을 강제 종료합니다.
   else{
   cout<<"Duplication User : "
    <<pic.identify
    <<"\n\a";
   }	//파일 내에 중복된 사용자가 있을경우 알려줍니다.
  }

  if(count == 50){
   cout << ".";
   count = 0;
  }	//위에  사용된 count가 50이 되었을 경우 '.'을 표시하고 count를 0으로 초기화합니다.
 }
 cout <<"Organize User Table completed!\t"<<user<<"Users\n\n";
 cout<<endl;
 return;
}

char getChoice(void){
 int choice;
 bool valid;

 cout<< "==========================================\n"
  << " 1. Search User\n"
  << " 2. Add User\n"
  << " 3. Delete Uer\n"
  << " 4. Exit\n\n"
  << "Enter your choice : ";
  //사용자에게 입력을 유도합니다.
 do{
  cin>>choice;
  switch(choice){
  case 1:
  case 2:
  case 3:
  case 4:
   valid = true;
   break;	//사용자의 입력이 1, 2, 3, 4이면 valid을 true로 반환하여 곧 getChoice 함수 종료
  default:
   valid=false;
   cout<<"\aWrong choice! Retry with enter number\n";
   break;
  }
 }while(!valid);	//사용자에게 정상적인 입력을 받았을때까지 위의 do 하위 문 반복
 return choice;
}

void process(List <PICTURE,char*>&list)
{
 char choice;

 do{
  choice = getChoice();
  
  switch(choice){
  case 1:
   search(list);
   break;
  case 2:
   addnode(list);
   break;
  case 3:
   deletenode(list);
   break;
  case 4:
   break;
  }
 }
 while(choice!=4);
 return;
}	//위에서 받은 choice에 따라 각 함수로 연결

void search(List <PICTURE, char*>&list){
 char id[15];	//입력할 사용자 ID에 사용될 변수
 bool found;
 int numder = 0;

 PICTURE pic;

 cout << "Search User\n"
 << "Enter User ID : ";
 cin >> id;	//ID를 입력받아 id에 마운트

 found = list.searchNode(id, pic, numder);

 if(found){
  cout << "User : " << pic.identify <<"\n"<<"Info : "
   << pic.identify << ":" << pic.info<<"\n"
   << "Count : "
   << numder
   << "\n\n";
  numder = 0;	//결과를 출력하여 찾기횟수(number) 초기화
 }
 else{
  cout<<"We failed to find : "<<"id"<<"\n"<<"Count : "
   << numder
   << "\n\n";
  numder = 0;
 }
 return;
}	//found함수를 이용하여 검색

void addnode(List <PICTURE,char*>&list){
 PICTURE pic;
 char data[160];
 int i = 0, j = 0, numder = 0;
 int addResult;

 cout << "Add User\n" << "Input User Data : ";
 cin >> data;


 while(data[i] != '\0'){
  pic.info[j] = data[i];  // data[i]가 0이 아니면 데이터를 pic.info[j]에 적재합니다.
  i++;
  j++;
 }
 pic.info[j] = '\0';

 addResult =list.addNode(pic, numder);

 if(addResult != 0){
  if(addResult == -1){
   cout<<"Memory Overflow! Halting..\a\n";
   exit(120);
  }
  else{
  cout<< "We can't add user "
   << pic.identify<<".."
   << "Count : "
   << numder
   << "\n\n";
  numder = 0;
  }
 }
 else{
  cout << "We added User "<<pic.identify
   <<". Count : "<< numder
   << "\n\n";
  numder = 0;
 }
}

void deletenode(List <PICTURE,char*>&list){
 char id[15];
 bool found;
 int numder = 0;

 PICTURE pic;

 cout << "Remove User\n" << "Enter ID that remove : ";
 cin >> id;

 found = list.searchNode(id, pic, numder);

 if(found){
  cout << pic.identify << ":"
   <<pic.info
   << " Removed. Count : "
   << numder
   << "\n\n";
  found = list.removeNode(id, &pic);
  numder = 0;
 }
 else{
  cout<<"User ID :  "<<id
   <<" is not found. Cancelling..\n\n";
 }

 return;
}

