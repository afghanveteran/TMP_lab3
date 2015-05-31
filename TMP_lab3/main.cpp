//
//  main.cpp
//  TMP_lab3
//
//  Created by Alexey Samorukov on 06/04/15.
//  Copyright (c) 2015 Alexey Samorukov. All rights reserved.
//

#include <iostream>
#include <conio.h>
#include <locale.h>
using namespace std;

class list{
    list *l=0x00, *first=0x00;//переменные
    int i;//для перемещения
    
public:
    list *lN, *lP;
    int inf;
    list(){
        lN = lP = 0x00;
    }
    list(list *prev, list *next){
        lP = prev;
        lN = next;
    }
    int addUp(int inf){//Добавить вверх
        l = first;
        i = 0;
        while (l!=0x00 && l->lN != 0x00){
            i++;
            l = l->lN;
        }
        if (l != 0x00){
            l->lN = new list();
            l->lN->lP = l;
            l->lN->inf = inf;
        }
        else{
            first = l = new list();
            l->inf = inf;
        }
        return 0;
    }
    int addIn(int n, int inf){//Добавить в определённое место
        l = first;
        i = 0;
        while (l!=0x00 && l->lN != 0x00 && i<n){
            i++;
            l = l->lN;
        }
        if (i < n) addUp(inf);
        else{
            if (l != 0x00){
                l = new list(l->lP, l);
                if (l->lP != 0x00){
                    l->lP->lN = l;
                }
                else first = l;
                if (l->lN != 0x00) l->lN->lP = l;
                l->inf = inf;
            }
            else{
                first = l = new list();
                l->inf = inf;
            }
        }
        return 0;
    }
    int addDown(int inf){//Добавить вниз
        l = first;
        if (l != 0x00){
            first= l->lP = new list();
            first->lN = l;
            first->inf = inf;
        }
        else{
            first = l = new list();
            l->inf = inf;
        }
        return 0;
    }
    int delUp(){//Удалить сверху
        l = first;
        i = 0;
        while (l != 0x00 && l->lN != 0x00){
            i++;
            l = l->lN;
        }
        if (l != 0x00){
            if (l->lP == 0x00) first = 0x00;
            else l->lP->lN = 0x00;
            delete(l);
        }
        else{
            return 2;
        }
        return 0;
    }
    int delIn(int n){//Удалить из определённого места
        l = first;
        i = 0;
        while (l != 0x00 && l->lN != 0x00 && i<n){
            i++;
            l = l->lN;
        }
        if (l != 0x00){
            if (l->lP == 0x00 && l->lN == 0x00) first = 0x00;
            if (l->lP != 0x00 && l->lN != 0x00){ l->lP->lN = l->lN; l->lN->lP = l->lP; }
            if (l->lP != 0x00 && l->lN == 0x00){ l->lP->lN = l->lN;}
            if (l->lP == 0x00 && l->lN != 0x00){ l->lN->lP = l->lP; }
            
            delete(l);
        }
        else{
            return 2;
        }
        return 0;
    }
    int delDown(){//Удалить снизу
        l = first;
        if (l != 0x00){
            if (l->lN == 0x00) first = 0x00;
            else{
                first = l->lN;
                l->lN->lP = 0x00;
            }
            delete(l);
        }
        else{
            return 2;
        }
        return 0;
    }
    void print(){
        l = first;
        i = 0;
        if (l != 0x00){
            while (l != 0x00){
                cout << "> [" << i << "] #" << l << " -> " << l->inf << "\n";
                i++;
                l = l->lN;
            }
        }
        else{
            cout << "> Список пуст!\n";
        }
    }
};

struct deck{
    int nU, nD, max;
    int **d;
    /*deck(){
     n = 0;
     }*/
    //Конструктор
    deck(){
        int i;
        d = new int* [100000];
        for (i = 0; i < 100000; i++) d[i] = 0x00;//Обнуляем все указатели
        max = 100000;
        nU = 0;//Верхний элемент
        nD = 0;//Нижний элемент
    }
    //Проверка не пуст ли дек
    bool isEmpty(){
        if (nU==nD) return 1;
        else return 0;
    }
    //Добавить элемент сверху
    int push(int *ptr){
        if (nU != max){
            d[nU] = ptr;
            nU++;
            
            return 0;
        }
        else return 1;
    }
    //Вытолкнуть элемент снизу
    int pop(){
        if (!isEmpty()){
            
            delete(d[nD]);
            d[nD] = 0x00;
            nD++;
            return 0;
        }
        else return 2;
    }
    void print(){
        int p = nD;
        if (p < 0) p = 0;
        cout << "> #" << d[p] << "->" << (d[p] == 0 ? 0 : *d[p]) << "\n";
    }
    ~deck(){
        delete(d);
    }
};

struct stack{
    int n, max;
    int **st;
    /*stack(){
     n = 0;
     }*/
    //Конструктор
    stack(){
        int i;
        st = new int*[100000];
        for (i = 0; i < 100000; i++) st[i] = 0x00;//Обнуляем все указатели
        max = 100000;
        n = 0;//Верхний элемент
    }
    //Проверка не пуст ли стек
    bool isEmpty(){
        if (st[0] == 0x00) return 1;
        else return 0;
    }
    //Добавить элемент сверху
    int push(int *ptr){
        if ((n) != max){
            st[n] = ptr;
            n++;
            
            return 0;
        }
        else return 1;
    }
    //Вытолкнуть элемент сверху
    int pop(){
        if (!isEmpty()){
            
            n--;
            delete(st[n]);
            st[n] = 0x00;
            return 0;
        }
        else return 2;
    }
    void print(){
        int p = n - 1;
        if (p < 0) p = 0;
        cout << "> #" <<st[p] << "->" << (st[p]==0?0:*st[p]) << "\n";
    }
    ~stack(){
        delete(st);
    }
};

int main(){
    int n, inf;
    char c;
    int* ptr;
    
    setlocale(LC_ALL, "russian");
    cout << "Добро пожаловать!";
    
    while (1){
        cout << "\ns - стек\nd - дек\nl - список\nBackspace - выход\n";
        cout << "> ";
        c = _getche();
        if (c == 8) break;//Backspase
        if (c == 's') {
            stack st;//Вызываем конструктор стека
            
            cout << "\n+ - добавить\n- - удалить\np - печать\nBackspace - выход\n";
            
            while (1){
                
                cout << "> ";
                c = _getche();
                //printf("%c = %d\n", c,c);
                
                if (c == 'p'){
                    st.print();
                }
                if (c == 8) break;//Backspase
                if (c == '+'){
                    cout << "> ";
                    ptr = new int;
                    cin >> *ptr;
                    
                    if (st.push(ptr) == 0) cout << "Добавлено\n";
                    else cout << "Не удалось добавить!\n";
                }
                if (c == '-'){
                    if (st.pop() == 0) cout << "> Удалено\n";
                    else cout << "> Стек пуст!\n";
                }
            }
        }
        if (c == 'd') {
            deck d;//Вызываем конструктор дека
            
            cout << "\n+ - добавить\n- - удалить\np - печать\nBackspace - выход\n";
            
            while (1){
                
                cout << "> ";
                c = _getche();
                //printf("%c = %d\n", c,c);
                
                if (c == 'p'){
                    d.print();
                }
                if (c == 8) break;//Backspase
                if (c == '+'){
                    cout << "> ";
                    ptr = new int;
                    cin >> *ptr;
                    
                    if (d.push(ptr) == 0) cout << "Добавлено\n";
                    else cout << "Не удалось добавить!\n";
                }
                if (c == '-'){
                    if (d.pop() == 0) cout << "> Удалено\n";
                    else cout << "> Дек пуст!\n";
                }
            }
        }
        if (c == 'l'){
            list l;
            
            cout << "\n+ - добавить вверх\n* - добавить вниз\n- - удалить сверху\n/ - удалить снизу\n= - добавить определённое место\n_ - удалить с определённого места\np - печать\nBackspace - выход\n";
            
            while (1){
                
                cout << "> ";
                c = _getche();
                //printf("%c = %d\n", c,c);
                
                if (c == 'p'){
                    l.print();
                }
                if (c == 8) break;//Backspase
                if (c == '+'){
                    cout << "> ";
                    cin >> inf;
                    
                    if (l.addUp(inf) == 0) cout << "Добавлено\n";
                    else cout << "Не удалось добавить!\n";
                }
                if (c == '*'){
                    cout << "> ";
                    cin >> inf;
                    
                    if (l.addDown(inf) == 0) cout << "Добавлено\n";
                    else cout << "Не удалось добавить!\n";
                }
                if (c == '='){
                    cout << "> в>";
                    cin >> n;
                    
                    cout << "> ";
                    cin >> inf;
                    
                    if (l.addIn(n, inf) == 0) cout << "Добавлено\n";
                    else cout << "Не удалось добавить!\n";
                }
                if (c == '-'){
                    if (l.delUp() == 0) cout << "> Удалено\n";
                    else cout << "> Список пуст!\n";
                }
                if (c == '/'){
                    if (l.delDown() == 0) cout << "> Удалено\n";
                    else cout << "> Список пуст!\n";
                }
                if (c == '_'){
                    cout << "> в>";
                    cin >> n;
                    if (l.delIn(n) == 0) cout << "> Удалено\n";
                    else cout << "> Список пуст!\n";
                }
            }
        }
    }
    
    cout << "\nПока!\n";
    
    //_getch();
    return 0;
}
