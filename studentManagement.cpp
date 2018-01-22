#include<iostream>
#include<string.h>
#include <iomanip>
#include <sstream> 
using namespace std;
typedef struct Snode * pointer;
int length = 0;
struct Snode{
	string number;
	string name;
	string className;
	string sex;
	string phone;
	string course; 
	pointer next;
	pointer prev;
};
struct Sort{
	string number;
	pointer next;
}studentData[100];
struct elective{
	string courseId;
	string courseName;
	string time;
}course[100];

struct Mode{
	char courseName[30],time[20],courseId[6];
};

typedef pointer lklist;
void interface(lklist student);
lklist initlist(){
	pointer head;
	head = new Snode;
	head->next = NULL;
	head->prev = NULL;
	return head;
}
void createDate(lklist s){
	pointer p;
	int i = 0;
	char number[13], name[7],className[8],sex[3],phone[12],course[50]; 
	FILE *fp = fopen("studentData.txt","rb");
	if(fp == NULL){
		return;
	}
	while(fscanf(fp,"%s%s%s%s%s%s",number,name,className, sex,phone,course) != -1){
		p = new Snode;
		p->number = number;
		p->name = name;
		p->className = className;
		p->sex = sex;
		p->phone = phone;
		p->course = course;
		s->next = p;
		p->prev = s;
		s = p;
		studentData[i].number = number;
		studentData[i].next = s;
		i++;
	}
	s->next = NULL;
	studentData[i].next = NULL;
	length = i-1;
}
void quickSort(Sort* arr,int startPos, int endPos){
	int i, j; 
 	string key; 
	key = arr[startPos].number; 
	Sort temp = arr[startPos];
	i = startPos; 
	j = endPos; 
	while (i<j){
		while (arr[j].number >= key && i<j)--j; 
  		arr[i] = arr[j]; 
   		while (arr[i].number <= key && i<j)++i; 
  		arr[j] = arr[i];
  	}
  	arr[i] = temp; 
  	if (i - 1>startPos) quickSort(arr, startPos, i - 1); 
 	if (endPos>i + 1) quickSort(arr, i + 1, endPos);
}
pointer BinSearch(string str){
	int mid = 0,low = 0,high = length;
	while(low <= high){
		mid = (low+high)/2;
		if(str < studentData[mid].number) high = mid - 1;
		else if(str > studentData[mid].number) low  = mid + 1;
		else return studentData[mid].next->prev;
	}
	return NULL;
}
//插入数据 
void insert(lklist s){
	pointer p,p1;
	FILE *fp = fopen("studentData.txt","a");
	int k = 0,i;
	char number[13], name[7],className[8],sex[3],phone[12],course[50]; 
	p = s->next;
	while(p->next != NULL)
		p = p->next;
	cout<<"------------------------------------插入学生信息-----------------------------------"<<endl;
	cout<<"请输入学生的信息，包括学号，姓名，班级，性别，手机号码，选修课程!"<<endl;
	p1 = new Snode;
	cin>>number>>name>>className>>sex>>phone>>course;
	if(BinSearch(number) != NULL){
		cout<<"学生学号重复,请重新输入学生信息!" <<endl;
		insert(s);
		return;
	}
	p1->number = number;
	p1->name = name;
	p1->className = className;
	p1->sex = sex;
	p1->phone = phone;
	p1->course = course;
	p->next = p1;
	p1->prev = p;
	p1->next = NULL;
	for(i=0;i<=length;i++)
 		if(studentData[i].number >= p1->number){  
			k = i;
			break;
		}
	 for(i=length;i>=k;i--)
 		studentData[i+1] = studentData[i];
 	studentData[k].number = p1->number;
 	studentData[k].next = p1;
	length++;
	fprintf(fp,"%s %s %s %s %s %s\n",number,name,className,sex,phone,course);
	fclose(fp);
	interface(s);
}
//输出所有数据 
void output(lklist s){
	pointer p1;
	int i = 0;
	p1 = s->next;
	cout<<endl;
	cout<<"------------------------------------******************-----------------------------------"<<endl;
	cout<<"输出学生所有信息如下： "<<endl; 
	while(p1 != NULL){
		cout<<p1->number<<" "<<p1->name<<"   "<<p1->className<<" "<<p1->sex<<" "<<p1->phone<<" "<<p1->course<<" "<<endl;
		p1 = p1->next;
	}
	interface(s);
}
//查询数据 
void search(lklist s){
	pointer p1;
	string sno;
	cout<<"------------------------------------******************-----------------------------------"<<endl;
	cout<<"请输入要查询信息学生的学号:  ";
	cin>>sno;
	p1 = BinSearch(sno);
	if(p1 != NULL){
		p1 = p1->next;
		cout<<p1->number<<" "<<p1->name<<"   "<<p1->className<<" "<<p1->sex<<" "<<p1->phone<<" "<<p1->course<<" "<<endl;
	}else{
		cout<<"该学生不存在！,请重新输入！"<<endl;
		search(s);
		return ;
	}
	cout<<endl;
	interface(s); 
}
//删除数据
void delete_(lklist s){
	string sno;
	pointer pSno,pFront;
	cout<<"------------------------------------******************-----------------------------------"<<endl;
	cout<<"请输入要删除学生的学号: ";
	cin>>sno;
	if(BinSearch(sno) != NULL){
		pFront = BinSearch(sno);
		pSno = pFront->next;
	}else{
		cout<<"该学生不存在！,请重新输入！"<<endl;
		delete_(s);
		return ;
	}
	if(pSno->next != NULL){
		pFront->next = pSno->next;
		delete pSno;
	}
	cout<<"---------------数据删除成功！--------------------";
	interface(s);
	return;
}
//修改数据
void alter(lklist s){
	string sno;
	char name[7];
	char value[30];
	pointer p1;
	cout<<"------------------------------------******************-----------------------------------"<<endl;
	cout<<"请输入要修改数据学生的学号: ";
	cin>>sno;
	if(BinSearch(sno) != NULL)
		p1 = BinSearch(sno); 
	else return;
	if(BinSearch(sno) != NULL){
		p1 = BinSearch(sno); 
		p1 = p1->next;
	}else{
		cout<<"该学生不存在！,请重新输入！"<<endl;
		alter(s);
		return ;
	}      
	cout<<"请输入要修改的字段(姓名，班级，性别，手机号码，选修课程):  "<<endl;
	cin>>name;
	cout<<"请输入要修改的字段值:  ";
	cin>>value;
	if(name == "姓名"){
		p1->name = value; 
	}else if(name == "班级"){
		p1->className = value;
	}else if(name == "性别"){
		p1->sex = value;
	}else if(name == "手机号码"){
		p1->phone = value;
	}else if(name == "选修课程"){
		p1->course = value;
	}
	interface(s); 
}
//按学号排序输出 
void sorting(lklist s){
	for(int i = 0;i<=length;i++){
		cout<<studentData[i].next->number<<" "<<studentData[i].next->name<<"   "<<studentData[i].next->className<<" ";
		cout<<studentData[i].next->sex<<" "<<studentData[i].next->phone<<" "<<studentData[i].next->course<<" "<<endl;
	}
	interface(s);
}
//学生选课  
void getElective(lklist s){
	int i = 0;
	pointer pso;
	char courseName[30],time[20],courseId[6];
	long length = 0;
	string sno,num;
	FILE *fp = fopen("elective.txt","rb");
	while(fscanf(fp,"%s%s%s",courseId,courseName,time) != -1){
		course[i].courseId = courseId;
		course[i].courseName = courseName;
		course[i].time = time;
		i++; 
	} 
	length = i - 1;
	cout<<"请输入学号: ";
	cin>>sno;
	pso = BinSearch(sno)->next; 
	cout<<"-----------------------------------学生选课表如下-----------------------------------"<<endl;
	for(i= 0;i<=length;i++){
		cout<<course[i].courseId<<"   "<<left<<setw(16)<<course[i].courseName<<course[i].time<<endl;
	}
	cout<<"输入选课编号(一次输入一个数)：";
	cin>>num;
	for(int j = 0;j<=length;j++){
		if(course[j].courseId == num){
			pso->course += "  " + course[j].courseName;
		}
	}
	fclose(fp);
	interface(s);
}
//xue
void addElective(){
	FILE *fp = fopen("elective.txt","rb");
	int i = 0;
	char courseName[30],time[20],courseId[6];
	cout<<"----------------------------------增加选课表------------------------------------"<<endl;
	cout<<"输入信息（课程id,课程名，开课时间): ";
	while(fscanf(fp,"%s%s%s",courseId,courseName,time) != -1){
		course[i].courseId = courseId;
		course[i].courseName = courseName;
		course[i].time = time;
		i++; 
	} 
	fclose(fp);
	cin>>courseId>>courseName>>time;
	for(int j = 0;j<i; j++){
		if(course[j].courseId == courseId){
			cout<<"课程ID已存在，请重新输入！"<<endl;
			addElective();
			return;
		}
	}
	fp = fopen("elective.txt","rb");
	fprintf(fp,"%s %s  %s\n",courseId,courseName,time);
	fclose(fp);
}
//删除课程 
void removeElective(lklist s){
	Mode temp[100];
	char courseName[30],time[20],courseId[6];
	int j = 0,i = 0,num;
	FILE *fp = fopen("elective.txt","rb");
	string number;
	while(fscanf(fp,"%s%s%s",courseId,courseName,time) != -1){
		strcpy(temp[j].courseId,courseId);
		strcpy(temp[j].courseName,courseName);
		strcpy(temp[j].time,time);
		j++;
	}
	fclose(fp);
	cout<<"----------------------------------删除选课记录------------------------------------"<<endl;
	cout<<"请输入要删除的课程id: "; 
	cin>>number;
	FILE *fp1 = fopen("elective.txt","w+b");
	for(; i<j; i++){
		if(temp[i].courseId != number){
			fprintf(fp1,"%s %s %s\n",temp[i].courseId,temp[i].courseName,temp[i].time);
		}
	}
	cout<<"删除成功,回到主界面！"<<endl;
	fclose(fp1);
	interface(s);
}
void interface(lklist student){
	int num = 1;
	cout<<"----------------------------------主界面------------------------------------"<<endl;
	cout<<"-------------------------"<<"添加学生输入:         	1"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"删除学生输入:         	2"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"修改学生输入:        	3"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"查询学生输入:        	4"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"按学号排序输入: 	5"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"在线选课输入:         	6"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"输出所有信息:         	7"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"增加选课表:         	8"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"删除选课记录:         	9"<<"---------------------------"<<endl;
	cout<<"-------------------------"<<"回到主界面:         	10"<<"---------------------------"<<endl;
	cout<<"----------------------------------------------------------------------------"<<endl;
	cout<<"请选择操作功能:  ";
	cin>>num;
	if(num <= 0 || num >= 11){
		cout<<"输入有误！"; 
		return;
	}
	switch(num){
		case 1:
			insert(student);
			break;
		case 2:
			delete_(student);
			break;
		case 3:
			alter(student);
			break;
		case 4: 
			search(student);
			break;
		case 5: 
			sorting(student);
			break;
		case 6: 
			getElective(student);
			break;
		case 7: 
			output(student);
			break;
		case 8: 
			addElective();;
			break;
		case 9: 
			removeElective(student); 
			break;
		case 10: 
			interface(student); 
			break;
		default: 
			return;
	}
}
int main(){
	lklist student;
	student = initlist();
	createDate(student);
	quickSort(studentData,0,length);
	interface(student); 
	return 0;
}
