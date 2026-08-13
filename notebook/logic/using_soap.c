#include "fossil/io/soap.h"
#include "fossil/io/output.h"

int main()
{
    const char *text =
        "THIS IS SOME CLICKBAIT!!! you won't believe what happened next...";

    /**
     * Demonstrate SOAP detection, sanitization, grammar/style analysis, and scoring.
     * This includes detecting clickbait and brain rot, sanitizing text, analyzing grammar/style,
     * scoring readability/clarity/quality, and processing the text through the full pipeline.
     */
    int is_clickbait = fossil_io_soap_detect(text, "clickbait");
    int is_brainrot  = fossil_io_soap_detect(text, "brain_rot");

    fossil_io_printf("Clickbait: %d\n", is_clickbait);
    fossil_io_printf("Brain rot: %d\n", is_brainrot);

    /**
     * Sanitize the text
     * This removes any potentially harmful content from the text.
     */
    char *clean = fossil_io_soap_sanitize(text);
    fossil_io_printf("Sanitized: %s\n", clean);

    /**
     * Analyze grammar and style
     * This provides insights into the writing style and passive voice usage.
     */
    fossil_io_soap_grammar_style_t gs =
        fossil_io_soap_analyze_grammar_style(text);

    fossil_io_printf("Style: %s\n", gs.style);
    fossil_io_printf("Passive voice %%: %d\n", gs.passive_voice_pct);

    /**
     * Score the text
     * This provides a numerical assessment of the text's readability, clarity, and quality.
     */
    fossil_io_soap_scores_t scores = fossil_io_soap_score(text);

    fossil_io_printf("Readability: %d\n", scores.readability);
    fossil_io_printf("Clarity: %d\n", scores.clarity);
    fossil_io_printf("Quality: %d\n", scores.quality);

    /**
     * Process the text through the full SOAP pipeline
     * This combines detection, sanitization, grammar/style analysis, and scoring into a single step.
     */
    char *processed = fossil_io_soap_process(text);
    fossil_io_printf("Processed: %s\n", processed);

    // cleanup
    free(clean);
    free(processed);

    return 0;
}
