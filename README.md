# Send email via Sendgrid in C
This very small repo is a starting point if you want to use C to send email via Sendgrid.

## Prerequisites
- Create API in Sendgrid and give minimum permission "Mail Send" https://docs.sendgrid.com/ui/account-and-settings/api-keys
- C compiler (e.g., GCC)
- [libcurl](https://curl.se/libcurl/) library

### Building

1. Clone the repository:
```
git clone https://github.com/evanTheTerribleWarrior/sendgrid-mail-send-c-example.git
cd sendgrid-mail-send-c-example
```

2. Add your API Key:
Go to `main.c` and in line 27 add your API Key you created on Sendgrid

3. Build the project using `make`:
- For Linux and Mac:
  ```
  make
  ```

- For Windows (with MinGW installed):
  ```
  mingw32-make
  ```

This will compile the program using the Makefile provided.

### Running the Program
To run the program, use the following command:

- For Linux and Mac:
```
./sendgrid_send_email -f sender@example.com -t recipient@example.com -s "Test Email" -c "Hello, World!"
```

- For Windows:
```
sendgrid_send_email.exe -f sender@example.com -t recipient@example.com -s "Test Email" -c "Hello, World!"
```
