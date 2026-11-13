https://youtu.be/8NlOhl1wFoc

- IMPORTANT: Carleton's anyconnect VPN interferes with wsl's networking, these instructions are only guaranteed to work if you are physically on Carleton campus.


ASSUMPTIONS
- Ubuntu is installed and this repository is already cloned.
- PostgreSQL is running on an OpenStack VM on port 5432.
- The VM has a floating IP, SSH access, and an existing PostgreSQL role named student.
- You can SSH to the VM and have sudo permissions there.
- Commands below are run from the repository's A3 directory unless stated otherwise.


1. INSTALL DEPENDENCIES (LOCAL UBUNTU / WSL)

sudo apt update
sudo apt install -y build-essential libpqxx-dev libpq-dev postgresql-client openssh-client

2. CREATE DATABASE (ON OPENSTACK VM)

ssh <SSH_USER>@<FLOATING_IP>
sudo -u postgres createdb -O student student_crud
exit

3. START SSH TUNNEL (LOCAL UBUNTU / WSL)

ssh -N -L 5433:127.0.0.1:5432 <SSH_USER>@<FLOATING_IP>

Leave this terminal open. Run subsequent commands in a second terminal.

4. POSTGRESQL PASSWORD (LOCAL UBUNTU / WSL)

nano ~/.pgpass

Add this line (substitute the actual password for the student database role):
127.0.0.1:5433:student_crud:student:<POSTGRES_PASSWORD>

chmod 600 ~/.pgpass

5. CREATE TABLE AND SEED DATA

psql -h 127.0.0.1 -p 5433 -U student -d student_crud -v ON_ERROR_STOP=1 -f sql/schema.sql
psql -h 127.0.0.1 -p 5433 -U student -d student_crud -v ON_ERROR_STOP=1 -f sql/seed.sql

Check:
psql -h 127.0.0.1 -p 5433 -U student -d student_crud -c "SELECT * FROM students ORDER BY student_id;"

6. BUILD AND RUN

make clean
make
./a3