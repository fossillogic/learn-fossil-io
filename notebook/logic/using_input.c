#include "fossil/io/output.h"
#include "fossil/io/input.h"

/**
 * Example usage of Fossil I/O Input functions.
 * This program demonstrates reading user input, validating it, and sanitizing it using the Fossil I/O library.
 * It also shows how to use various validation functions for integers, floats, emails, and password strength.
 */
int main(void)
{
    char username[128];
    char sanitized[128];
    int age;
    float salary;
    int flags;

    /**
     * Read user input for username
     * The input is read using fossil_io_gets, which safely reads a line of input into the provided buffer.
     * The input is then trimmed of whitespace and validated for suspicious patterns.
     */
    fossil_io_puts("Enter username: ");
    if (fossil_io_gets(username, sizeof(username)) != 0)
    {
        fossil_io_printf("{red}Failed to read input.{normal}\n");
        return 1;
    }

    fossil_io_trim(username);

    /**
     * Validate the username for suspicious patterns
     * The function fossil_io_validate_is_suspicious_user checks if the username contains any suspicious patterns.
     * If it does, a warning message is displayed to the user.
     */
    if (fossil_io_validate_is_suspicious_user(username))
    {
        fossil_io_printf("{yellow}Warning:{normal} Username looks suspicious.\n");
    }

    /**
     * Sanitize the username for generic use
     * The function fossil_io_validate_sanitize_string sanitizes the username for generic use.
     */
    flags = fossil_io_validate_sanitize_string(
        username,
        sanitized,
        sizeof(sanitized),
        FOSSIL_CTX_GENERIC);

    /**
     * Display the sanitized username and any flags indicating modifications or detections
     * The sanitized username is displayed, and any flags indicating modifications or detections are also shown.
     */
    fossil_io_printf("Sanitized username: {cyan}%s{normal}\n", sanitized);

    if (flags & FOSSIL_SAN_MODIFIED)
        fossil_io_printf("{yellow}Input was modified during sanitization.{normal}\n");

    if (flags & FOSSIL_SAN_SCRIPT)
        fossil_io_printf("{red}Script content detected.{normal}\n");

    if (flags & FOSSIL_SAN_SQL)
        fossil_io_printf("{red}SQL injection patterns detected.{normal}\n");

    if (flags & FOSSIL_SAN_SHELL)
        fossil_io_printf("{red}Shell command patterns detected.{normal}\n");

    /**
     * Integer validation
     * The function fossil_io_validate_is_int checks if the input is a valid integer.
     */
    if (fossil_io_validate_is_int("42", &age))
    {
        fossil_io_printf("Parsed age: {green}%d{normal}\n", age);
    }

    /**
     * Float validation
     * The function fossil_io_validate_is_float checks if the input is a valid float.
     */
    if (fossil_io_validate_is_float("1234.56", &salary))
    {
        fossil_io_printf("Parsed salary: {green}%.2f{normal}\n", salary);
    }

    /**
     * Email validation
     * The function fossil_io_validate_is_email checks if the input is a valid email address.
     */
    if (fossil_io_validate_is_email("user@example.com"))
    {
        fossil_io_printf("{green}Email is valid.{normal}\n");
    }

    /**
     * Password strength check
     * The function fossil_io_validate_is_weak_password checks if the password is weak.
     */
    if (fossil_io_validate_is_weak_password(
            "password123",
            sanitized,
            "user@example.com"))
    {
        fossil_io_printf("{red}Weak password detected.{normal}\n");
    }
    else
    {
        fossil_io_printf("{green}Password looks strong.{normal}\n");
    }

    /**
     * Disposable email detection
     * The function fossil_io_validate_is_disposable_email checks if the email is from a disposable email provider.
     */
    if (fossil_io_validate_is_disposable_email("test@mailinator.com"))
    {
        fossil_io_printf("{yellow}Disposable email detected.{normal}\n");
    }

    /**
     * Bot detection
     * The function fossil_io_validate_is_suspicious_bot checks if the user-agent indicates a bot.
     */
    if (fossil_io_validate_is_suspicious_bot(
            "Mozilla/5.0 (compatible; Googlebot/2.1)"))
    {
        fossil_io_printf("{yellow}Bot user-agent detected.{normal}\n");
    }

    return 0;
}
