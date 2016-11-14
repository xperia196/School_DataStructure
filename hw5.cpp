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
};	//��带 �����մϴ�.

template<class TYPE, class KTYPE>
class List{
     private:
       NODE<TYPE> *head;
       NODE<TYPE> *pos;
       NODE<TYPE> *rear;
       int count;
    
    bool _add(NODE<TYPE> *pPre, TYPE dataIn);	//����ڸ� �߰��ϴ� �Լ� ����
    void _delete (NODE<TYPE> *pPre, NODE<TYPE> *pLoc, TYPE *dataOutPtr);	//����ڸ� �����ϴ� �Լ� ����
    bool _search (NODE<TYPE> **pPre, NODE<TYPE> **pLoc, KTYPE identify, int& numder);	//����ڸ� �˻��ϴ� �Լ� ����
	
  public:
   List(void);
   ~List(void);
   int addNode(TYPE dataIn, int& numder);
   bool removeNode(KTYPE identify, TYPE *dataOutPtr);
   bool searchNode(KTYPE identify, TYPE& dataOut, int& numder);
};	//����Ʈ�� ȣȯ�ϴ� List Ŭ������ �����մϴ�.

template<class TYPE, class KTYPE>
List<TYPE, KTYPE> :: List(void){
 head = NULL;
 pos = NULL;
 rear = NULL;
 count = 0;
}	//List���� �������� �� �� �ֵ��� �մϴ�.

template<class TYPE, class KTYPE>
int List<TYPE, KTYPE> :: addNode(TYPE dataIn, int& numder){

 bool found;
 bool success;
 
 NODE<TYPE> *pPre;
 NODE<TYPE> *pLoc;
 
 found = _search(&pPre, &pLoc, dataIn.identify, numder);
 if(found)
  return(+1);	//Ű�� �ߺ��Ǿ��ٸ� +1�� �����մϴ�.
 success = _add(pPre, dataIn);
 if(!success)
  return(-1);	//�������� �����÷ο�(Overflow)�� �߻��ϸ� -1�� �����մϴ�.
 return(0);
} // ��� �߰� ���ø� ����

template<class TYPE, class KTYPE>
bool List<TYPE, KTYPE> :: _add(NODE<TYPE> *pPre, TYPE dataIn){

 NODE<TYPE> *pNew;

 if(!(pNew = new NODE<TYPE>))
  return false;	//�߰��� ��尡 �̹� ����ȭ�Ǿ������� false�� ��ȯ�մϴ�.
 pNew->data = dataIn;
 pNew->link = NULL;
 if(pPre == NULL)
 {
  pNew->link = head;
  head = pNew;
 }	//pPre�� ������ ù ����� ���̳� �� ����Ʈ�� �����մϴ�.
 else
 {
  pNew->link = pPre->link;
  pPre->link = pNew;
 }	//pPre�� ���� �Ͽ� �߰�, �Ǵ� ���� �����մϴ�.
 if(pNew->link == NULL)
  rear = pNew;	//����Ʈ�� �������� ���ԵǾ� ������ �� ����Ʈ�� �����մϴ�.
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
  _delete(pPre, pLoc, pDataOut);	//��尡 �߰ߵǾ��ٸ�, �װ��� �����մϴ�.
 return found;
}	//��� ���� ���ø� ����

template <class TYPE, class KTYPE>
void List<TYPE, KTYPE> :: _delete(NODE<TYPE> *pPre, NODE<TYPE> *pLoc, TYPE *pDataOut){
 *pDataOut = pLoc->data;
 if(pPre == NULL)
  head = pLoc->link;
 else
  pPre->link = pLoc->link;
 if(pLoc->link == NULL)
  rear = pPre;
 count--;	//���� ���� �� �ϳ� ���̱�
 delete pLoc;	//�޸� ��ȯ
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
	//��带 ã�Ҵٸ�, dataOut�� ã�� �����͸� ������ �˴ϴ�.
 return found;
}	//��� ã�� ���ø� ����

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
 }	//������ �ѹ��� �ѷ����� ���� ã�� �õ�

 if(strcmp(identify, (*pLoc)->data.identify) == 0)
  return true; //ã�⿡ ���������� true ��ȯ
 else
  return false;	//�װ� �ƴϸ�(ã�⿡ ����������) false ��ȯ
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
}	//����Ʈ�� �����ϰ�, �޸𸮸� ��ȯ�Ͽ� ȿ�������� ���ҽ� Ȱ��

struct PICTURE{
 char identify[15];	//����� ID�� ������ ����
 char info[140];	//������� ��Ÿ ������ ������ ����
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
 return 0;	//��� �����۾����� �Լ���� �̷���� �����Ƿ� ������(process)���� ������ ���� ���α׷��� �����մϴ�.
}

void init(List <PICTURE, char*>& list){
 ifstream fileIO;
 int addResult;
 PICTURE pic;
 int user = 0, count = 0, numder = 0;

 fileIO.open("passwd"); //������ ������.
 if(!fileIO){   
  cerr<<"\a We can't Open the file. Halting.. \n";
  exit(110);	//������ ���ٸ� �����޽����� ǥ���ϰ�, ���α׷��� ���� �����մϴ�.
 }

 cout << "Organizing User Table\n"
  << "Reading file and establishing Table\n";
 
 while(!fileIO.eof()){
  fileIO.getline(pic.identify, sizeof(pic.identify), ':');
  fileIO.getline(pic.info, sizeof(pic.info));
  user += 1;	//':'�� �б�� ������ �� �྿ ������ ��� �н��ϴ�.
  addResult =list.addNode(pic, numder);
  count++;	//1���� �о���϶����� count�� 1�� �����մϴ�.

  if(addResult != 0){
   if(addResult == -1){
    cout<<"Memory Overflow. Halting..\n";
    exit(120);
   }	//�޸𸮰� �����÷ο� �� ���, �����޽����� ǥ���ϰ� ���α׷��� ���� �����մϴ�.
   else{
   cout<<"Duplication User : "
    <<pic.identify
    <<"\n\a";
   }	//���� ���� �ߺ��� ����ڰ� ������� �˷��ݴϴ�.
  }

  if(count == 50){
   cout << ".";
   count = 0;
  }	//����  ���� count�� 50�� �Ǿ��� ��� '.'�� ǥ���ϰ� count�� 0���� �ʱ�ȭ�մϴ�.
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
  //����ڿ��� �Է��� �����մϴ�.
 do{
  cin>>choice;
  switch(choice){
  case 1:
  case 2:
  case 3:
  case 4:
   valid = true;
   break;	//������� �Է��� 1, 2, 3, 4�̸� valid�� true�� ��ȯ�Ͽ� �� getChoice �Լ� ����
  default:
   valid=false;
   cout<<"\aWrong choice! Retry with enter number\n";
   break;
  }
 }while(!valid);	//����ڿ��� �������� �Է��� �޾��������� ���� do ���� �� �ݺ�
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
}	//������ ���� choice�� ���� �� �Լ��� ����

void search(List <PICTURE, char*>&list){
 char id[15];	//�Է��� ����� ID�� ���� ����
 bool found;
 int numder = 0;

 PICTURE pic;

 cout << "Search User\n"
 << "Enter User ID : ";
 cin >> id;	//ID�� �Է¹޾� id�� ����Ʈ

 found = list.searchNode(id, pic, numder);

 if(found){
  cout << "User : " << pic.identify <<"\n"<<"Info : "
   << pic.identify << ":" << pic.info<<"\n"
   << "Count : "
   << numder
   << "\n\n";
  numder = 0;	//����� ����Ͽ� ã��Ƚ��(number) �ʱ�ȭ
 }
 else{
  cout<<"We failed to find : "<<"id"<<"\n"<<"Count : "
   << numder
   << "\n\n";
  numder = 0;
 }
 return;
}	//found�Լ��� �̿��Ͽ� �˻�

void addnode(List <PICTURE,char*>&list){
 PICTURE pic;
 char data[160];
 int i = 0, j = 0, numder = 0;
 int addResult;

 cout << "Add User\n" << "Input User Data : ";
 cin >> data;


 while(data[i] != '\0'){
  pic.info[j] = data[i];  // data[i]�� 0�� �ƴϸ� �����͸� pic.info[j]�� �����մϴ�.
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

