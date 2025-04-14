#include<iostream>
#include<cstdlib>
#include<clocale>
#include<string>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include <limits>
#define MaxContacts 1000
//下次再随便定义数据类型我头撞公交车
using namespace std;
class AddressList{
public:
    string name;
    string TelNum;
    string EMail;
    string QQ;
    string Address;
    AddressList() : name(""), TelNum(""), EMail(""), QQ(""), Address("") {}
    AddressList(string name1,string TelNum1,string EMail1,string QQ1,string Address1)
    {
        name=name1;
        TelNum=TelNum1;
        EMail=EMail1;
        QQ=QQ1;
        Address=Address1;
    }

    copyList(const AddressList& other) {
    name = other.name;
    TelNum = other.TelNum;
    EMail = other.EMail;
    QQ = other.QQ;
    Address = other.Address;
    }
    AddressList& operator=(const AddressList& other) {
        if (this != &other) {  // 避免自我赋值
            name = other.name;
            TelNum = other.TelNum;
            EMail = other.EMail;
            QQ = other.QQ;
            Address = other.Address;
        }
        return *this;
    }
    ~AddressList() {}  // 通常什么都不做，除非有需要释放的资源
    string getName() const { return name; }
    void setName(const string& name) { this->name = name; }
    // 对于其他的变量也应该有类似的getter和setter函数
    string getTelNum() const { return TelNum; }
    void setTelNum(const string& TelNum) { this->TelNum = TelNum; }
    string getEMail() const { return EMail; }
    void setEMail(const string& EMail) { this->EMail = EMail; }
    string getQQ() const { return QQ; }
    void setQQ(const string& QQ) { this->QQ = QQ; }
    string getAddress() const { return Address; }
    void setAddress(const string& Address) { this->Address = Address; }

};
int main(){
    std::ifstream file1("AddressList.txt");
    if (!file1.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }
    std::unordered_map<std::string,AddressList> hashTable01;
    std::unordered_map<std::string,AddressList> hashTable02;
    //两个哈希表，一个给姓名，一个给电话；
    std::string line;
    while (std::getline(file1, line)) { // 逐行读取文件内容
        std::istringstream iss(line); // 将字符串流转换为输入流
        AddressList address("","","","","");
        iss >> address.name >> address.TelNum >> address.EMail >> address.QQ >> address.Address;
         // 从输入流中读取数据并存入AddressList对象中
        hashTable01[address.getName()] = address;
        hashTable02[address.getTelNum()] = address;
    }
    int flag=1;
    int dialog01;
    int dialog02=1;
    int dialog03;
    while(flag!=0)
    {
        /*以下是界面和操作部分*/
        printf("-------------------------------------------------\n");
        printf("\t欢迎使用E人脉，请选择一个开始的方法吧!\n");
        printf("\n\t输入1选择添加联系人\n");
        printf("\n\t输入2选择编辑联系人\n");
        printf("\n\t输入3选择删除联系人\n");
        printf("\n\t输入4选择搜索联系人\n");
        printf("\n\t输入5选择以姓名为关键字输出所有联系人\n");
        printf("\n\t输入6选择以电话为关键字输出所有联系人\n");
        printf("\n\t输入其他任意数字则退出本软件\n");
        printf("\n\t请输入您的指令：");
        std::cin>>dialog01;
        printf("-------------------------------------------------\n");
        if(dialog01==1)
        {
            dialog02++;
            /*运行保障，dialog02必须在每一循环开启的时候始终维持在正数*/
            /*因为dialog02=0是很多分支的停机条件*/
            printf("\tAdding\n");
            while(dialog02!=0){
                dialog03=1;
                AddressList adl01("","","","","");
                std::string adls;
                std::cout<<"\t请输入联系人姓名，不超过50字符"<<std::endl;
                printf("\t");
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                while(dialog03!=0){
                    std::getline(std::cin,adls);
                    if(adls.length()>51){
                        std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                        adls.clear();
                        printf("\t");
                        //太长了，清空重来;
                    }
                    else if(hashTable01.find(adls)!=hashTable01.end()){
                        std::cout<<"\t该名字已被占用，请重新输入！"<<std::endl;
                        adls.clear();
                        printf("\t");
                        //因为所有空名字在校验以后都是自动填充的unknowname，所以不用考虑对空字符串的哈希校验问题;
                    }
                    else dialog03=0;
                }
                if(adls == "") {
                    adls = "UnknownName"; // 设置默认值
                }
                adl01.setName(adls);
                adls.clear();
                /*-----------------------------------------*/
                dialog03++;
                std::cout<<"\t请输入联系人电话，不超过20字符"<<std::endl;
                printf("\t");
                while(dialog03!=0){
                    std::getline(std::cin,adls);
                    if(adls.length()>21){
                        std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                        adls.clear();
                        printf("\t");
                        //太长了，清空重来;
                    }
                    else dialog03=0;
                }
                if(adls == "") {
                    adls = "UnknownTel";
                }
                adl01.setTelNum(adls);
                adls.clear();
                /*-----------------------------------------*/
                dialog03++;
                std::cout<<"\t请输入联系人电子邮件地址，不超过256字符"<<std::endl;
                printf("\t");
                while(dialog03!=0){
                    std::getline(std::cin,adls);
                    if(adls.length()>256){
                        std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                        adls.clear();
                        printf("\t");
                        //太长了，清空重来;
                    }
                    else dialog03=0;
                }
                if(adls == "") {
                    adls = "UnknownEMail";
                }
                adl01.setEMail(adls);
                adls.clear();
                /*-----------------------------------------*/
                dialog03++;
                std::cout<<"\t请输入联系人QQ号码，不超过12字符"<<std::endl;
                printf("\t");
                while(dialog03!=0){
                    std::getline(std::cin,adls);
                    if(adls.length()>12){
                        std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                        adls.clear();
                        printf("\t");
                        //太长了，清空重来;
                    }
                    else dialog03=0;
                }
                if(adls == "") {
                    adls = "0000000000";
                }
                adl01.setQQ(adls);
                adls.clear();
                /*-----------------------------------------*/
                dialog03++;
                std::cout<<"\t请输入联系人住址，不超过150字符"<<std::endl;
                printf("\t");
                while(dialog03!=0){
                    std::getline(std::cin,adls);
                    if(adls.length()>151){
                        std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                        adls.clear();
                        printf("\t");
                        //太长了，清空重来;
                    }
                    else dialog03=0;
                }
                if(adls == "") {
                    adls = "Address";
                }
                adl01.setAddress(adls);
                adls.clear();
                /*-----------------------------------------*/
                hashTable01[adl01.getName()]=adl01;
                hashTable02[adl01.getTelNum()]=adl01;
                std::cout<<"\t输入0退出添加操作，输入其他任意数字可继续添加"<<std::endl;
                std::cout<<"\t请输入您的指令"<<std::endl;
                printf("\t");
                std::cin>>dialog02;
            }
            printf("\n\t输入0直接退出本软件\n");
            printf("\t输入1返回主界面\n");
            printf("\t请输入您的指令：");
            scanf("%d%*c",&flag);
        }
        else if(dialog01==2)
        {
            //todo:没完事呢；
            dialog02++;
            printf("\tEditing\n");
            std::cout<<"\t选择1可以按照用户名查找编辑"<<std::endl;
            std::cout<<"\t选择2可以按照电话号码查找编辑"<<std::endl;
            std::cout<<"\t警告：选项2可能会导致超出预期的后果"<<std::endl;
            std::cout<<"\t请根据您的搜索需求选择指令"<<std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            dialog03=1;
            int qlc;
            printf("\t");
            std::cin>>qlc;
            if(qlc==1){
                while(dialog02!=0){
                    std::string adls2;
                    std::cout<<"\t请输入联系人姓名，不超过50字符"<<std::endl;
                    printf("\t");
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while(dialog03!=0){
                        std::getline(std::cin,adls2);
                        if(adls2.length()>51){
                            std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                            adls2.clear();
                            printf("\t");
                            //太长了，清空重来;
                        }
                        else dialog03=0;
                    }
                    dialog03++;
                    if(hashTable01.find(adls2)!=hashTable01.end()){
                        AddressList adl03=hashTable01[adls2];
                        //使用operator[]方法实现输出信息重新来过；
                        //因为需要编辑信息所以不能直接删；
                        std::cout<<"\t您将要编辑的联系人如下："<<std::endl;
                        std::cout<<"\t"<<adl03.getName()<<"\n\t"<<adl03.getTelNum()<<"\n\t"
                        <<adl03.getEMail()<<"\n\t"<<adl03.getQQ()<<"\n\t"
                        <<adl03.getAddress()<<std::endl;
                        std::cout<<"\t输入1则开始编辑"<<std::endl;
                        std::cout<<"\t输入2则取消编辑"<<std::endl;
                        std::cout<<"\t请输入您的指令："<<std::endl;
                        printf("\t");
                        int select;
                        std::cin>>select;
                        if(select==1){
                            AddressList adl01;
                            std::string adls;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout<<"\t请输入联系人姓名，不超过50字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>51){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else if(hashTable01.find(adls)!=hashTable01.end()){
                                    std::cout<<"\t该名字已被占用，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //因为所有空名字在校验以后都是自动填充的unknowname，所以不用考虑对空字符串的哈希校验问题;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getName(); // 设置默认值
                            }
                            adl01.setName(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            dialog03++;
                            std::cout<<"\t请输入联系人电话，不超过20字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>21){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getTelNum();
                            }
                            adl01.setTelNum(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            dialog03++;
                            std::cout<<"\t请输入联系人电子邮件地址，不超过256字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>256){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getEMail();
                            }
                            adl01.setEMail(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            dialog03++;
                            std::cout<<"\t请输入联系人QQ号码，不超过12字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>12){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getQQ();
                            }
                            adl01.setQQ(adls);
                            adls.clear();
                            dialog03++;
                            std::cout<<"\t请输入联系人住址，不超过150字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>151){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getAddress();
                            }
                            adl01.setAddress(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            hashTable01.erase(adls2);
                            hashTable02.erase(adl03.getTelNum());
                            hashTable01[adl01.getName()]=adl01;
                            hashTable02[adl01.getTelNum()]=adl01;
                            /*甚至这里还有些问题，如果不先删除旧元素的话有时无法写入新元素*/
                            std::cout<<"\t编辑操作已完成"<<std::endl;
                        }
                        else{std::cout<<"\t编辑操作已取消"<<std::endl;}
                    }
                    else{
                        std::cout<<"\t该联系人不存在！"<<std::endl;
                        adls2.clear();
                    }
                    std::cout<<"\t输入0退出编辑，输入其他任意数字可继续编辑"<<std::endl;
                    std::cout<<"\t请输入您的指令"<<std::endl;
                    printf("\t");
                    std::cin>>dialog02;
                }
            }
            else if(qlc==2){
                while(dialog02!=0){
                    dialog03=1;
                    std::string adls2;
                    std::cout<<"\t请输入联系人电话，不超过50字符"<<std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    printf("\t");
                    while(dialog03!=0){
                        std::getline(std::cin,adls2);
                        if(adls2.length()>21){
                            std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                            adls2.clear();
                            printf("\t");
                            //太长了，清空重来;
                        }
                        else dialog03=0;
                    }
                    dialog03++;
                    if(hashTable02.find(adls2)!=hashTable02.end()){
                        AddressList adl03=hashTable02[adls2];
                        //使用operator[]方法实现输出信息重新来过；
                        //因为需要编辑信息所以不能直接删；
                        std::cout<<"\t您将要编辑的联系人如下："<<std::endl;
                        std::cout<<"\t"<<adl03.getName()<<"\n\t"<<adl03.getTelNum()<<"\n\t"
                        <<adl03.getEMail()<<"\n\t"<<adl03.getQQ()<<"\n\t"
                        <<adl03.getAddress()<<std::endl;
                        std::cout<<"\t输入1则开始编辑"<<std::endl;
                        std::cout<<"\t输入2则取消编辑"<<std::endl;
                        std::cout<<"\t请输入您的指令："<<std::endl;
                        int select;
                        printf("\t");
                        std::cin>>select;
                        if(select==1){
                            AddressList adl01;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::string adls;
                            std::cout<<"\t请输入联系人姓名，不超过50字符"<<std::endl;

                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>51){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else if(hashTable01.find(adls)!=hashTable01.end()){
                                    std::cout<<"\t该名字已被占用，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //因为所有空名字在校验以后都是自动填充的unknowname，所以不用考虑对空字符串的哈希校验问题;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getName(); // 设置默认值
                            }
                            adl01.setName(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            dialog03++;
                            std::cout<<"\t请输入联系人电话，不超过20字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>21){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getTelNum();
                            }
                            adl01.setTelNum(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            dialog03++;
                            std::cout<<"\t请输入联系人电子邮件地址，不超过256字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>256){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getEMail();
                            }
                            adl01.setEMail(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            dialog03++;
                            std::cout<<"\t请输入联系人QQ号码，不超过12字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>12){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getQQ();
                            }
                            adl01.setQQ(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            dialog03++;
                            std::cout<<"\t请输入联系人住址，不超过150字符"<<std::endl;
                            printf("\t");
                            while(dialog03!=0){
                                std::getline(std::cin,adls);
                                if(adls.length()>151){
                                    std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                                    adls.clear();
                                    printf("\t");
                                    //太长了，清空重来;
                                }
                                else dialog03=0;
                            }
                            if(adls == "") {
                                adls = adl03.getAddress();
                            }
                            adl01.setAddress(adls);
                            adls.clear();
                            /*-----------------------------------------*/
                            hashTable02.erase(adls2);
                            hashTable01.erase(adl03.getName());
                            hashTable01[adl01.getName()]=adl01;
                            hashTable02[adl01.getTelNum()]=adl01;

                            std::cout<<"\t编辑操作已完成"<<std::endl;
                        }
                        else{std::cout<<"\t编辑操作已取消"<<std::endl;}
                    }
                    else{
                        std::cout<<"\t该联系人不存在！"<<std::endl;
                        adls2.clear();
                    }
                    std::cout<<"\t输入0退出编辑，输入其他任意数字可继续编辑"<<std::endl;
                    std::cout<<"\t请输入您的指令"<<std::endl;
                    printf("\t");
                    std::cin>>dialog02;
                }
            }
            printf("\n\t输入0直接退出本软件\n");
            printf("\t输入1返回主界面\n");
            printf("\t请输入您的指令：");
            scanf("%d%*c",&flag);
        }
        else if(dialog01==3)
        {
            dialog02++;
            printf("\tDeleting\n");
            std::cout<<"\t选择1可以按照用户名删除"<<std::endl;
            std::cout<<"\t选择2可以按照电话号码删除"<<std::endl;
            std::cout<<"\t警告：选项2可能会导致"<<std::endl;
            std::cout<<"\t请根据您的搜索需求选择指令"<<std::endl;
            int qlc;
            printf("\t");
            std::cin>>qlc;
            if(qlc==1){
                while(dialog02!=0){
                    dialog03=1;
                    std::string adls;
                    std::cout<<"\t请输入联系人姓名，不超过50字符"<<std::endl;
                    printf("\t");
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while(dialog03!=0){
                        std::getline(std::cin,adls);
                        if(adls.length()>51){
                            std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                            adls.clear();
                            printf("\t");
                            //太长了，清空重来;
                        }
                        else dialog03=0;
                    }
                    dialog03++;
                    if(hashTable01.find(adls)!=hashTable01.end()){
                        AddressList adl03=hashTable01[adls];
                        //使用operator[]方法实现输出信息重新来过；
                        std::cout<<"\t您将要删除的联系人如下："<<std::endl;
                        std::cout<<"\t"<<adl03.getName()<<"\n\t"<<adl03.getTelNum()<<"\n\t"
                        <<adl03.getEMail()<<"\n\t"<<adl03.getQQ()<<"\n\t"
                        <<adl03.getAddress()<<std::endl;
                        std::cout<<"\t输入1则开始删除"<<std::endl;
                        std::cout<<"\t输入2则取消删除"<<std::endl;
                        std::cout<<"\t请输入您的指令："<<std::endl;
                        int select;
                        printf("\t");
                        std::cin>>select;
                        if(select==1){
                            hashTable02.erase(adl03.getTelNum());
                            hashTable01.erase(adls);
                            std::cout<<"\t删除操作已完成"<<std::endl;
                        }
                        else{std::cout<<"\t删除操作已取消"<<std::endl;}
                    }
                    else{
                        std::cout<<"\t该联系人不存在！"<<std::endl;
                        adls.clear();
                    }
                    std::cout<<"\t输入0退出删除操作，输入其他任意数字可继续删除操作"<<std::endl;
                    std::cout<<"\t请输入您的指令"<<std::endl;
                    printf("\t");
                    std::cin>>dialog02;
                }
            }
            else if(qlc==2){
                while(dialog02!=0){
                    dialog03=1;
                    std::string adls;
                    std::cout<<"\t请输入联系人电话，不超过20字符"<<std::endl;
                    printf("\t");
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while(dialog03!=0){
                        std::getline(std::cin,adls);
                        if(adls.length()>51){
                            std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                            adls.clear();
                            printf("\t");
                            //太长了，清空重来;
                        }
                        else dialog03=0;
                    }
                    dialog03++;
                    if(hashTable02.find(adls)!=hashTable02.end()){
                        AddressList adl03=hashTable02[adls];
                        //使用operator[]方法实现输出信息重新来过；
                        std::cout<<"\t您将要删除的联系人如下："<<std::endl;
                        std::cout<<"\t"<<adl03.getName()<<"\n\t"<<adl03.getTelNum()<<"\n\t"
                        <<adl03.getEMail()<<"\n\t"<<adl03.getQQ()<<"\n\t"
                        <<adl03.getAddress()<<std::endl;
                        std::cout<<"\t输入1则开始删除"<<std::endl;
                        std::cout<<"\t输入2则取消删除"<<std::endl;
                        std::cout<<"\t请输入您的指令："<<std::endl;
                        int select;
                        printf("\t");
                        std::cin>>select;
                        if(select==1){
                            hashTable01.erase(adl03.getName());
                            hashTable02.erase(adls);
                            std::cout<<"\t删除操作已完成"<<std::endl;
                        }
                        else{std::cout<<"\t删除操作已取消"<<std::endl;}
                    }
                    else{
                        std::cout<<"\t该联系人不存在！"<<std::endl;
                        adls.clear();
                    }
                    std::cout<<"\t输入0退出删除操作，输入其他任意数字可继续删除操作"<<std::endl;
                    std::cout<<"\t请输入您的指令"<<std::endl;
                    printf("\t");
                    std::cin>>dialog02;
                }
            }
            printf("\n\t输入0直接退出本软件\n");
            printf("\t输入1返回主界面\n");
            printf("\t请输入您的指令：");
            scanf("%d%*c",&flag);
        }
        else if(dialog01==4)
        {
            dialog02++;
            printf("\tSearching\n");
            std::cout<<"\t选择1可以按照用户名查找"<<std::endl;
            std::cout<<"\t选择2可以按照电话号码查找"<<std::endl;
            std::cout<<"\t警告：选项2可能会导致超出预期的后果"<<std::endl;
            std::cout<<"\t请根据您的搜索需求选择指令"<<std::endl;
            int plc;
            printf("\t");
            std::cin>>plc;
            if(plc==1){
                while(dialog02!=0){
                    dialog03=1;
                    std::string adls;
                    std::cout<<"\t请输入联系人姓名，不超过50字符"<<std::endl;
                    printf("\t");
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while(dialog03!=0){
                        std::getline(std::cin,adls);
                        if(adls.length()>51){
                            std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                            adls.clear();
                            printf("\t");
                            //太长了，清空重来;
                        }
                        else dialog03=0;;
                    }
                    dialog03++;
                    if(hashTable01.find(adls)!=hashTable01.end()){
                        AddressList adl03=hashTable01[adls];
                        //使用operator[]方法实现输出信息重新来过；
                        std::cout<<"\t您要搜索的联系人如下："<<std::endl;
                        std::cout<<"\t"<<adl03.getName()<<"\n\t"<<adl03.getTelNum()<<"\n\t"
                        <<adl03.getEMail()<<"\n\t"<<adl03.getQQ()<<"\n\t"
                        <<adl03.getAddress()<<std::endl;
                    }
                    else{
                        std::cout<<"\t该联系人不存在！"<<std::endl;
                        adls.clear();
                    }
                    std::cout<<"\t输入0退出搜索，输入其他任意数字可继续搜索"<<std::endl;
                    std::cout<<"\t请输入您的指令"<<std::endl;
                    printf("\t");
                    std::cin>>dialog02;

                }
            }
            else if(plc==2){
                while(dialog02!=0){
                    dialog03=1;
                    std::string adls;
                    std::cout<<"\t请输入联系人电话，不超过20字符"<<std::endl;
                    printf("\t");
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while(dialog03!=0){
                        std::getline(std::cin,adls);
                        if(adls.length()>21){
                            std::cout<<"\t长度超标，请重新输入！"<<std::endl;
                            adls.clear();
                            printf("\t");
                            //太长了，清空重来;
                        }
                        else dialog03=0;
                    }
                    dialog03++;
                    if(hashTable02.find(adls)!=hashTable02.end()){
                        AddressList adl03=hashTable02[adls];
                        //使用operator[]方法实现输出信息重新来过；
                        std::cout<<"\t您要搜索的联系人如下："<<std::endl;
                        std::cout<<"\t"<<adl03.getName()<<"\n\t"<<adl03.getTelNum()<<"\n\t"
                        <<adl03.getEMail()<<"\n\t"<<adl03.getQQ()<<"\n\t"
                        <<adl03.getAddress()<<std::endl;
                    }
                    else{
                        std::cout<<"\t该联系人不存在！"<<std::endl;
                        adls.clear();
                    }
                    std::cout<<"\t输入0退出搜索，输入其他任意数字可继续搜索"<<std::endl;
                    std::cout<<"\t请输入您的指令"<<std::endl;
                    printf("\t");
                    std::cin>>dialog02;
                }
            }
            printf("\n\t输入0直接退出本软件\n");
            printf("\t输入1返回主界面\n");
            printf("\t请输入您的指令：");
            scanf("%d%*c",&flag);
        }
        else if(dialog01==5)
        {
            printf("\tPrintingByName\n");
            for (const auto& pair : hashTable01) {
                std::cout << "\tName: " << pair.second.name << ", TelNum: " << pair.second.TelNum
                <<",EMail: "<<pair.second.EMail <<",QQ: "<<pair.second.QQ<<",Address:"
                <<pair.second.Address<< std::endl;
            }
            printf("\n\t输入0直接退出本软件\n");
            printf("\t输入1返回主界面\n");
            printf("\t请输入您的指令：");
            scanf("%d%*c",&flag);
        }
        else if(dialog01==6)
        {
            printf("\tPrintingByTelNum\n");
            for (const auto& pair : hashTable02) {
                std::cout << "\tName: " << pair.second.name << ", TelNum: " << pair.second.TelNum
                <<",EMail: "<<pair.second.EMail <<",QQ: "<<pair.second.QQ<<",Address:"
                <<pair.second.Address<< std::endl;
            }
            printf("\n\t输入0直接退出本软件\n");
            printf("\t输入1返回主界面\n");
            printf("\t请输入您的指令：");
            scanf("%d%*c",&flag);
        }
        else break;
    }
    /*这个交互逻辑框架是用C写的demo，反正不是不能用，就不改了*/
    file1.close();
    /*以下是实现文件写入的部分*/
    std::ofstream file2("AddressList.txt");
    if(!file2.is_open()){
        std::cerr<<"打开错误！"<<std::endl;
        return 1;
    }
    file2.seekp(0,std::ios::beg);
    file2.write("",0);
    for (const auto& pair : hashTable01) {
        file2<< pair.second.getName() << " " << pair.second.getTelNum() << " " << pair.second.getEMail()
                   << " " << pair.second.getQQ() << " " << pair.second.getAddress() << std::endl;
    }
    file2.close();
    std::cout<<"-------------------------------------------------"<<std::endl;
    std::cout<<"\t感谢您的使用，我们下次再见！"<<std::endl;
    return 0;
}
