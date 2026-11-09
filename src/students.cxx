#include "students.hxx"

void getAllStudents(pqxx::connection& db) {
    pqxx::read_transaction tx(db);
    auto result = tx.exec("SELECT * FROM students ORDER BY student_id");
    tx.commit();

    std::cout << "Students in database:\n";
    for (const auto& row : result) {
        std::cout << "ID: " << row["student_id"].as<int>()
                    << ", Name: " << row["first_name"].as<std::string>()
                    << " " << row["last_name"].as<std::string>()
                    << ", Email: " << row["email"].as<std::string>()
                    << ", Enrollment Date: " << row["enrollment_date"].as<std::string>()
                    << '\n';
    }
}

int addStudent(
    pqxx::connection& db,
    const std::string& first_name,
    const std::string& last_name,
    const std::string& email,
    const std::string& enrollment_date
){
    pqxx::work tx(db);
    try {
        auto result = tx.exec(
            "INSERT INTO students (first_name, last_name, email, enrollment_date) "
            "VALUES ($1, $2, $3, $4) RETURNING student_id",
            pqxx::params(first_name, last_name, email, enrollment_date)
        );
        tx.commit();
        return result[0]["student_id"].as<int>();
    } catch (const std::exception& e) {
        std::cerr << "Error adding student: " << e.what() << '\n';
        return -1;
    }
}

bool updateStudentEmail(
    pqxx::connection& db,
    int student_id,
    const std::string& new_email
){
    pqxx::work tx(db);
    try {
        auto result = tx.exec(
            "UPDATE students SET email = $1 WHERE student_id = $2",
            pqxx::params(new_email, student_id)
        );
        tx.commit();
        return result.affected_rows() > 0;
    } catch (const std::exception& e) {
        std::cerr << "Error updating student email: " << e.what() << '\n';
        return false;
    }
}

bool deleteStudent(
    pqxx::connection& db,
    int student_id
){
    pqxx::work tx(db);
    try {
        auto result = tx.exec(
            "DELETE FROM students WHERE student_id = $1",
            pqxx::params(student_id)
        );
        tx.commit();
        return result.affected_rows() > 0;
    } catch (const std::exception& e) {
        std::cerr << "Error deleting student: " << e.what() << '\n';
        return false;
    }
}