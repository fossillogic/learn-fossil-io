#include "fossil/io/output.h"
#include "fossil/io/input.h"

#include <iostream>
#include <string>

using namespace fossil::io;

int main()
{
    std::string username;

    out << "Enter username: ";
    std::getline(std::cin, username);

    /**
     * Validate the username for suspicious patterns
     * The function Input::is_suspicious_user checks if the username contains any suspicious patterns.
     * If it does, a warning message is displayed to the user.
     */
    if (Input::is_suspicious_user(username))
    {
        out << "{yellow}Warning:{normal} Suspicious username.\n";
    }

    /**
     * Sanitize the username for generic use
     * The function Input::validate_sanitize_string sanitizes the username for generic use.
     */
    int flags = Input::validate_sanitize_string(
        username,
        FOSSIL_CTX_GENERIC);

    out << "Sanitized username: {cyan}" << username << "{normal}\n";

    if (flags & FOSSIL_SAN_MODIFIED)
        out << "{yellow}Input was modified.{normal}\n";

    if (flags & FOSSIL_SAN_SQL)
        out << "{red}SQL injection patterns detected.{normal}\n";

    if (flags & FOSSIL_SAN_SCRIPT)
        out << "{red}Script patterns detected.{normal}\n";

    /**
     * Integer validation
     * The function Input::validate_is_int checks if the input is a valid integer.
     */
    int age;
    if (Input::validate_is_int("42", &age))
    {
        out << "Age = {green}" << age << "{normal}\n";
    }

    /**
     * Float validation
     * The function Input::validate_is_float checks if the input is a valid float.
     */
    float score;
    if (Input::validate_is_float("98.5", &score))
    {
        out << "Score = {green}" << score << "{normal}\n";
    }

    /**
     * Email validation
     * The function Input::validate_is_email checks if the input is a valid email address.
     */
    if (Input::validate_is_email("user@example.com"))
    {
        out << "{green}Email is valid.{normal}\n";
    }

    /**
     * Password strength check
     * The function Input::is_weak_password checks if the password is weak.
     */
    if (Input::is_weak_password(
            "SuperSecurePassword!2026",
            username,
            "user@example.com"))
    {
        out << "{red}Weak password.{normal}\n";
    }
    else
    {
        out << "{green}Strong password.{normal}\n";
    }

    /**
     * Disposable email detection
     * The function Input::is_disposable_email checks if the email is from a disposable email provider.
     */
    if (Input::is_disposable_email("test@mailinator.com"))
    {
        out << "{yellow}Disposable email detected.{normal}\n";
    }

    /**
     * Bot detection
     * The function Input::is_suspicious_bot checks if the user-agent indicates a bot.
     */
    if (Input::is_suspicious_bot(
            "Mozilla/5.0 (compatible; Bingbot/2.0)"))
    {
        out << "{yellow}Bot detected.{normal}\n";
    }

    return 0;
}
