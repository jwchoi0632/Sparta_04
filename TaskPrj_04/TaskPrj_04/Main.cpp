#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std; // namespace std 사용

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
    vector<Book> books; // 책 목록 저장

    Book* findBookByTitle(string title)
    {
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return nullptr;
        }

        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].title == title)
            {
                cout << "도서명 '" << title << "' 도서의 정보가 존재합니다." << endl;
                cout << "도서명 : " << title << endl;
                cout << "저자명 : " << books[i].author << endl;
                return &books[i];
            }
        }

        cout << "도서명 '" << title << "'인 도서 정보를 찾을 수 없습니다." << endl;
        return nullptr;
    }

    Book* findBookByAuthor(string author)
    {
        if (books.empty())
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return nullptr;
        }

        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].author == author)
            {
                cout << "저자명 '" << author << "' 도서의 정보가 존재합니다." << endl;
                cout << "도서명 : " << books[i].title << endl;
                cout << "저자명 : " << author << endl;
                return &books[i];
            }
        }

        cout << "저자명 '" << author << "'인 도서 정보를 찾을 수 없습니다." << endl;
        return nullptr;
    }

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
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
                cout << "도서 " << title << "을 대여했습니다." << endl;
            }
            else
            {
                cout << "도서 " << title << "의 재고가 없습니다." << endl;
            }
        }
        else
        {
            cout << "도서관에 " << title << "의 정보가 없습니다." << endl;
            cout << "검색하신 도서 정보를 다시 확인해주시기 바랍니다." << endl;
        }
    }

    void returnBook(string title)
    {
        if (stock.find(title) != stock.end())
        {
            if (stock[title] < 3)
            {
                stock[title] += 1;
                cout << "도서 " << title << "을 반납했습니다." << endl;
            }
            else
            {
                cout << "도서의 재고가 가득 찼습니다." << endl;
                cout << "도서의 출처를 확인해주시기 바랍니다." << endl;
            }
        }
        else
        {
            cout << "도서관에 " << title << "의 정보가 없습니다." << endl;
            cout << "다른 도서관에서 대여한 책인지 확인하시기 바랍니다." << endl;
        }
    }

    bool checkBorrowable(string title)
    {
        if (stock.find(title) != stock.end())
        {
            if (stock[title] > 0)
            {
                cout << "도서 " << title << "의 재고 : " << stock[title] << endl;
                cout << "해당 도서는 대여가 가능합니다." << endl;
                return true;
            }
            else
            {
                cout << "도서 " << title << "의 재고가 없습니다." << endl;
                cout << "해당 도서는 대여가 불가능합니다." << endl;
                return false;
            }
        }
        else
        {
            cout << "도서관에 " << title << "의 정보가 없습니다." << endl;
            cout << "검색하신 도서 정보를 다시 확인해주시기 바랍니다." << endl;
            return false;
        }
    }

    void displayAllStock()
    {
        size_t count = 0;

        if (stock.empty())
        {
            cout << "대여 가능한 도서 목록이 존재하지 않습니다." << endl;
            return;
        }

        cout << "대여 가능 도서 목록" << endl;

        for (map<string, int>::iterator it = stock.begin(); it != stock.end(); ++it)
        {
            if (it->second > 0)
            {
                count++;
                cout << "- " << it->first << ", 재고 : " << it->second << endl;
            }
        }

        if (count == 0)
        {
            cout << "대여 가능한 도서 목록이 존재하지 않습니다." << endl;
        }
    }
};

Book* searchProcess(BookManager* manager_book)
{
    while (true)
    {
        cout << "\n책 검색을 선택하셨습니다." << endl;
        cout << "1. 도서명으로 검색" << endl;
        cout << "2. 저자명으로 검색" << endl;
        cout << "3. 메인으로 돌아가기" << endl;
        cout << "선택 : ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            string title;
            cout << "\n도서명으로 검색을 시작합니다." << endl;
            cout << "도서명 : ";
            cin.ignore();
            getline(cin, title);

            return manager_book->getBookByTitle(title);
        }
        else if (choice == 2)
        {
            string author;
            cout << "\n저자명으로 검색을 시작합니다." << endl;
            cout << "저자명 : ";
            cin.ignore();
            getline(cin, author);

            return manager_book->getBookByAuthor(author);
        }
        else if (choice == 3)
        {
            cout << "메인 화면으로 돌아갑니다." << endl;

            return nullptr;
        }
        else
        {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }
}

void borrowProcess(BorrowManager* manager_borrow, Book* book)
{
    while (true)
    {
        cout << "\n해당 도서의 대여 정보를 확인하시겠습니까?" << endl;
        cout << "1. 대여 정보 확인" << endl;
        cout << "2. 메인으로 돌아가기" << endl;
        cout << "선택 : ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            bool check = manager_borrow->checkBorrowable(book->title);

            if (check)
            {
                cout << "\n도서를 대여하시겠습니까?" << endl;
                cout << "1.YES" << endl;
                cout << "2.NO" << endl;
                cout << "선택 : ";

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
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }
}

int main() {
    BookManager* manager_book = new BookManager();
    BorrowManager* manager_borrow = new BorrowManager();

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 검색" << endl;
        cout << "4. 대여 가능 책 출력" << endl;
        cout << "5. 대여 도서 반납" << endl;
        cout << "6. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager_book->addBook(title, author); // 입력받은 책 정보를 추가
            manager_borrow->initializeStock(title);
        }
        else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
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
            cout << "\n반납할 도서의 제목을 입력해주세요" << endl;
            cout << "도서명 : ";
            cin.ignore();
            getline(cin, title);
            manager_borrow->returnBook(title);
        }
        else if (choice == 6) {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    delete manager_book;
    delete manager_borrow;

    return 0; // 프로그램 정상 종료
}
