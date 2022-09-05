#ifndef LIST_H
#define LIST_H


#include <iostream>



template <typename T>
class my_list{

	private:

		int node_count;

		struct node{
			T data;
			node *link;
		}*head,*tail;

	public:

		my_list(){
			node_count = 0;
			head=nullptr;
			tail=nullptr;
		}

		~my_list(){
			node *temp;
			while(head != nullptr){
				temp = head;
				head = head->link;
				delete temp;
			}
			node_count = 0;
		}

		friend std::ostream& operator<< (std::ostream &o, const my_list<T> &list) {
			if(list.node_count == 0){return o;}
			const node *temp = list.head;
			o << "[" << temp->data;
			for (int i=1;i<list.node_count;i++){
				temp = temp->link;
				o << ", " << temp->data;
			}
			o << "]";
			return o;
		}

		my_list<T>& operator= (const my_list<T> &source){
			if(head == source.head){return *this;}

			node *temp;
			while(head != nullptr){
				temp = head;
				head = head->link;
				delete temp;
			}
			node_count = 0;

			head=nullptr;
			tail=nullptr;

			for(int i=0;i<source.node_count;i++){
				append(source.get_data(i));
			}
			return *this;
		}

		T& operator[] (const int &index){
			int node_number;
			if(index >= 0){node_number = index + 1;}
			else{node_number = node_count + index + 1;}
			if(node_number>node_count){node_number=node_count;}
			node *temp = head;
			for (int i=2;i<=node_number;i++){
				temp = temp->link;
			}
			return temp->data;
		}

		const T& get_data (const int &index)const{
			int node_number = index + 1;
			if(node_number>node_count){node_number=node_count;}
			const node *temp = head;
			for (int i=2;i<=node_number;i++){
				temp = temp->link;
			}
			return temp->data;
		}

		void join (my_list<T> &other){
			tail->link = other.head;
			tail = other.tail;
			node_count += other.node_count;
			other.head = nullptr;
			other.tail = nullptr;
			other.node_count = 0;
			return;
		}

		void append (const T &value){
			node *temp = new node;
			temp->data=value;
			temp->link=nullptr;
			if(head!=nullptr){
				tail->link=temp;
				tail=temp;
			}
			else{
				head=temp;
				tail=temp;
			}
			node_count++;
			return;
		}

		void append_arr (const T *arr,const int &size){
			if(size<1){return;}
			for(int i=0;i<size;i++){
				append(arr[i]);
			}
			return;
		}

		void insert (const int &index,const T &value){
			int node_number = index + 1;
			if((node_number>node_count)or(node_number<1)){return;}
			if(node_number!=1){
				node *prev=head,*next;
				for (int i=2;i<=node_number-1;i++){
					prev = prev->link;
				}
				next=prev->link;
				node *temp = new node;
				temp->data=value;
				temp->link=next;
				prev->link=temp;
			}
			else{
				node *temp = new node;
				temp->data=value;
				temp->link=head;
				head=temp;
			}
			node_count++;
			return;
		}

		void insert_arr (int index,const T *arr,const int &size){
			if(size<1){return;}
			for(int i=0;i<size;i++){
				insert(index,arr[i]);
				index++;
			}
			return;
		}

		void delete_node (const int &index){
			int node_number = index + 1;
			if((node_number>node_count)or(node_number<1)){return;}
			if(node_number==1){
				node *temp=head;
				head = head->link;
				delete temp;
			}
			else if(node_number==node_count){
				node *temp=head;
				for (int i=2;i<=(node_number-1);i++){
					temp = temp->link;
				}
				tail=temp;
				temp = temp->link;
				tail->link = nullptr;
				delete temp;
			}
			else{
				node *prev=head,*next;
				for (int i=2;i<=(node_number-1);i++){
					prev = prev->link;
				}
				next = prev->link;
				node *temp=next;
				next = next->link;
				prev->link=next;
				delete temp;
			}
			node_count--;
			return;
		}

		const int& node_counter()const{
			return node_count;
		}

		void reverse(){
			if(node_count <= 1){return;}
			node *curr=head,*prev=nullptr,*next=head->link;
			while(next != nullptr){
				curr->link = prev;
				prev = curr;
				curr = next;
				next = next->link;
			}
			curr->link = prev;
			tail = head;
			head = curr;
			return;
		}

		void clear(){
			node *temp;
			while(head != nullptr){
				temp = head;
				head = head->link;
				delete temp;
			}
			node_count = 0;
			return;
		}
};



#endif
