#include <iostream>
#include <pqxx/pqxx>
#include "students.hxx"

int main() {
    try {
        pqxx::connection db(
            "host=127.0.0.1 "
            "port=5433 "
            "dbname=student_crud "
            "user=student"
        );

        if (!db.is_open()) {
            std::cerr << "Database connection failed.\n";
            return 1;
        }

        std::cout << "Connected to PostgreSQL successfully!\n";


        std::cout << "Initial list of students:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        int new_student_id = addStudent(db, "Cloud", "Strife", "CloudStrife@seven.com", "2026-11-07");

        std::cout << "After adding a new student:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);


        updateStudentEmail(db, new_student_id, "CloudStrife@seven.ca");

        std::cout << "After updating the student's email:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);


        deleteStudent(db, new_student_id);
        std::cout << "After deleting the student:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        deleteStudent(db, new_student_id);
        std::cout << "After attempting to delete the deleted student again:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        updateStudentEmail(db, new_student_id, "CloudStrife@seven.org");
        std::cout << "After attempting to update the deleted student's email again:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        addStudent(
            db,
            "Sephiroth",
            "'); DROP TABLE students; --",
            "sephiroth@shinra.com",
            "2026-11-07"
        );
        std::cout << "After Sephiroth attempts to drop the table through SQL injection:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        addStudent(db, "Kefka", "Palazzo", "john.doe@example.com", "2026-11-07");
        std::cout << "After attempting to add Kefka with John's email:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        addStudent(db, "Terra", "Branford",
           "terra@example.com", "2026-99-99");
        std::cout << "After attempting to add Terra with an invalid date:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        updateStudentEmail(db, 2, "john.doe@example.com");
        std::cout << "After attempting to update Jane's email to John's existing email:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        updateStudentEmail(db, 2,
            "evil@example.com'; DROP TABLE students; --");
        std::cout << "After attempting to update Jane's email with SQL injection:\n";
        std::cout << "-------------------------\n";
        getAllStudents(db);

        std::cout << "\nEnd of program!!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Database error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}