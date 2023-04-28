#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Book {
private:
    string title;
    string author;
    int yearPublished;
public:
    Book(string t, string a, int y) : title(t), author(a), yearPublished(y) {}
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYearPublished() const { return yearPublished; }
};

class Library {
private:
    vector<Book> booksCatalogue;
public:
    void addBook(Book book) {
        // Проверяем, что книги с таким же названием и автором еще нет в каталоге
        auto iter = find_if(booksCatalogue.begin(), booksCatalogue.end(), [&](const Book& b) {
            return b.getTitle() == book.getTitle() && b.getAuthor() == book.getAuthor();
            });
        if (iter != booksCatalogue.end()) {
            cout << "Книга уже есть в каталоге!" << endl;
        }
        else {
            booksCatalogue.push_back(book);
            cout << "Книга добавлена в каталог." << endl;
        }
    }
    void removeBook(Book book) {
        auto iter = find_if(booksCatalogue.begin(), booksCatalogue.end(), [&](const Book& b) {
            return b.getTitle() == book.getTitle() && b.getAuthor() == book.getAuthor() && b.getYearPublished() == book.getYearPublished();
            });
        if (iter != booksCatalogue.end()) {
            booksCatalogue.erase(iter);
            cout << "Книга удалена из каталога." << endl;
        }
        else {
            cout << "Книга не найдена в каталоге!" << endl;
        }
    }
    vector<Book> searchBook(string title, string author, int yearPublished) {
        vector<Book> result;
        for (const auto& book : booksCatalogue) {
            if ((title.empty() || book.getTitle() == title) &&
                (author.empty() || book.getAuthor() == author) &&
                (yearPublished == -1 || book.getYearPublished() == yearPublished)) {
                result.push_back(book);
            }
        }
        return result;
    }
};

int main() {
    Library library;
    setlocale(LC_ALL, "Russian");
    library.addBook(Book("Мастер и Маргарита", "Михаил Булгаков", 1967));
    library.addBook(Book("Анна Каренина", "Лев Толстой", 1877));
    library.addBook(Book("Анна Каренина", "Лев Толстой", 1877)); // Попытка добавить книгу, которая уже есть в каталоге
    library.removeBook(Book("Анна Каренина", "Лев Толстой", 1877));
    vector<Book> searchResult = library.searchBook("Мастер и Маргарита", "Михаил Булгаков", -1);
    for (const auto& book : searchResult) {
        cout << book.getTitle() << " (" << book.getAuthor() << ", " << book.getYearPublished() << ")" << endl;
    }
    return 0;
}