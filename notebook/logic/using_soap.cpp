#include "fossil/io/soap.h"
#include "fossil/io/output.h"

int main()
{
    using fossil::io::Soap;

    std::string text =
        "THIS IS SOME CLICKBAIT!!! you won't believe what happened next...";

    /**
     * Demonstrate SOAP detection, sanitization, grammar/style analysis, and scoring.
     * This includes detecting clickbait and brain rot, sanitizing text, analyzing grammar/style,
     * scoring readability/clarity/quality, and processing the text through the full pipeline.
     */
    if (Soap::detect(text, "clickbait"))
        fossil::io::Output::printf("Clickbait detected\n");

    if (Soap::detect(text, "brain_rot"))
        fossil::io::Output::printf("Brain rot detected\n");

    /**
     * Sanitize the text
     * This removes any potentially harmful content from the text.
     */
    std::string clean = Soap::sanitize(text);
    fossil::io::Output::printf("Sanitized: %s\n", clean.c_str());

    /**
     * Analyze grammar and style
     * This provides insights into the writing style and passive voice usage.
     */
    auto gs = Soap::analyze_grammar_style(text);

    fossil::io::Output::printf("Style: %s\n", gs.style.c_str());
    fossil::io::Output::printf("Passive voice %%: %d\n", gs.passive_voice_pct);

    /**
     * Score the text
     * This provides a numerical assessment of the text's readability, clarity, and quality.
     */
    auto scores = Soap::score(text);

    fossil::io::Output::printf("Readability: %d\n", scores.readability);
    fossil::io::Output::printf("Clarity: %d\n", scores.clarity);
    fossil::io::Output::printf("Quality: %d\n", scores.quality);

    /**
     * Process the text through the full SOAP pipeline
     * This combines detection, sanitization, grammar/style analysis, and scoring into a single step.
     */
    std::string processed = Soap::process(text);
    fossil::io::Output::printf("Processed: %s\n", processed.c_str());

    return 0;
}
