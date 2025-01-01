#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std; // namespace std ���

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BookManager {
private:
    vector<Book> books; // å ��� ����

    Book* findBookByTitle(string title)
    {
        if (books.empty())
        {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return nullptr;
        }

        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].title == title)
            {
                cout << "������ '" << title << "' ������ ������ �����մϴ�." << endl;
                cout << "������ : " << title << endl;
                cout << "���ڸ� : " << books[i].author << endl;
                return &books[i];
            }
        }

        cout << "������ '" << title << "'�� ���� ������ ã�� �� �����ϴ�." << endl;
        return nullptr;
    }

    Book* findBookByAuthor(string author)
    {
        if (books.empty())
        {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return nullptr;
        }

        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].author == author)
            {
                cout << "���ڸ� '" << author << "' ������ ������ �����մϴ�." << endl;
                cout << "������ : " << books[i].title << endl;
                cout << "���ڸ� : " << author << endl;
                return &books[i];
            }
        }

        cout << "���ڸ� '" << author << "'�� ���� ������ ã�� �� �����ϴ�." << endl;
        return nullptr;
    }

public:
    // å �߰� �޼���
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back ���
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }

    // ��� å ��� �޼���
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    Book* getBookByTitle(string title)
    {
        return findBookByTitle(title);
    }

    Book* getBookByAuthor(string author)
    {
        return findBookByAuthor(author);
    }
};

class BorrowManager
{
private:
    map<string,int> stock;

public:
    void initializeStock(string title, int quantity = 3)
    {
        stock.insert(make_pair(title, quantity));
    }

    void borrowBook(string title)
    {
        if (stock.find(title) != stock.end())
        {
            if (stock[title] > 0)
            {
                stock[title] -= 1;
                cout << "���� " << title << "�� �뿩�߽��ϴ�." << endl;
            }
            else
            {
                cout << "���� " << title << "�� ��� �����ϴ�." << endl;
            }
        }
        else
        {
            cout << "�������� " << title << "�� ������ �����ϴ�." << endl;
            cout << "�˻��Ͻ� ���� ������ �ٽ� Ȯ�����ֽñ� �ٶ��ϴ�." << endl;
        }
    }

    void returnBook(string title)
    {
        if (stock.find(title) != stock.end())
        {
            if (stock[title] < 3)
            {
                stock[title] += 1;
                cout << "���� " << title << "�� �ݳ��߽��ϴ�." << endl;
            }
            else
            {
                cout << "������ ��� ���� á���ϴ�." << endl;
                cout << "������ ��ó�� Ȯ�����ֽñ� �ٶ��ϴ�." << endl;
            }
        }
        else
        {
            cout << "�������� " << title << "�� ������ �����ϴ�." << endl;
            cout << "�ٸ� ���������� �뿩�� å���� Ȯ���Ͻñ� �ٶ��ϴ�." << endl;
        }
    }

    bool checkBorrowable(string title)
    {
        if (stock.find(title) != stock.end())
        {
            if (stock[title] > 0)
            {
                cout << "���� " << title << "�� ��� : " << stock[title] << endl;
                cout << "�ش� ������ �뿩�� �����մϴ�." << endl;
                return true;
            }
            else
            {
                cout << "���� " << title << "�� ��� �����ϴ�." << endl;
                cout << "�ش� ������ �뿩�� �Ұ����մϴ�." << endl;
                return false;
            }
        }
        else
        {
            cout << "�������� " << title << "�� ������ �����ϴ�." << endl;
            cout << "�˻��Ͻ� ���� ������ �ٽ� Ȯ�����ֽñ� �ٶ��ϴ�." << endl;
            return false;
        }
    }

    void displayAllStock()
    {
        size_t count = 0;

        if (stock.empty())
        {
            cout << "�뿩 ������ ���� ����� �������� �ʽ��ϴ�." << endl;
            return;
        }

        cout << "�뿩 ���� ���� ���" << endl;

        for (map<string, int>::iterator it = stock.begin(); it != stock.end(); ++it)
        {
            if (it->second > 0)
            {
                count++;
                cout << "- " << it->first << ", ��� : " << it->second << endl;
            }
        }

        if (count == 0)
        {
            cout << "�뿩 ������ ���� ����� �������� �ʽ��ϴ�." << endl;
        }
    }
};

Book* searchProcess(BookManager* manager_book)
{
    while (true)
    {
        cout << "\nå �˻��� �����ϼ̽��ϴ�." << endl;
        cout << "1. ���������� �˻�" << endl;
        cout << "2. ���ڸ����� �˻�" << endl;
        cout << "3. �������� ���ư���" << endl;
        cout << "���� : ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            string title;
            cout << "\n���������� �˻��� �����մϴ�." << endl;
            cout << "������ : ";
            cin.ignore();
            getline(cin, title);

            return manager_book->getBookByTitle(title);
        }
        else if (choice == 2)
        {
            string author;
            cout << "\n���ڸ����� �˻��� �����մϴ�." << endl;
            cout << "���ڸ� : ";
            cin.ignore();
            getline(cin, author);

            return manager_book->getBookByAuthor(author);
        }
        else if (choice == 3)
        {
            cout << "���� ȭ������ ���ư��ϴ�." << endl;

            return nullptr;
        }
        else
        {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }
}

void borrowProcess(BorrowManager* manager_borrow, Book* book)
{
    while (true)
    {
        cout << "\n�ش� ������ �뿩 ������ Ȯ���Ͻðڽ��ϱ�?" << endl;
        cout << "1. �뿩 ���� Ȯ��" << endl;
        cout << "2. �������� ���ư���" << endl;
        cout << "���� : ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            bool check = manager_borrow->checkBorrowable(book->title);

            if (check)
            {
                cout << "\n������ �뿩�Ͻðڽ��ϱ�?" << endl;
                cout << "1.YES" << endl;
                cout << "2.NO" << endl;
                cout << "���� : ";

                cin >> choice;

                if (choice == 1) manager_borrow->borrowBook(book->title);
            }
            return;
        }
        else if (choice == 2)
        {
            return;
        }
        else
        {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }
}

int main() {
    BookManager* manager_book = new BookManager();
    BorrowManager* manager_borrow = new BorrowManager();

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. å �˻�" << endl;
        cout << "4. �뿩 ���� å ���" << endl;
        cout << "5. �뿩 ���� �ݳ�" << endl;
        cout << "6. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager_book->addBook(title, author); // �Է¹��� å ������ �߰�
            manager_borrow->initializeStock(title);
        }
        else if (choice == 2) {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager_book->displayAllBooks();
        }
        else if (choice == 3)
        {
            Book* book = searchProcess(manager_book);
            if (book != nullptr) borrowProcess(manager_borrow, book);
            book = nullptr;
        }
        else if (choice == 4)
        {
            manager_borrow->displayAllStock();
        }
        else if (choice == 5)
        {
            string title;
            cout << "\n�ݳ��� ������ ������ �Է����ּ���" << endl;
            cout << "������ : ";
            cin.ignore();
            getline(cin, title);
            manager_borrow->returnBook(title);
        }
        else if (choice == 6) {
            // 3�� ����: ����
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    delete manager_book;
    delete manager_borrow;

    return 0; // ���α׷� ���� ����
}
