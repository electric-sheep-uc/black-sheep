package data.values;

/**
 * The interface to automatically document the Enums that reflect the byte values for the
 * protocols such that this info can be used in the documentation wiki.
 */
public interface DocumentingMarkdown {

    default String header(){
        StringBuilder sb = new StringBuilder();
        sb.append("| Identifier | Byte Value |\n");
        sb.append("| ---------- | ---------- |\n");
        return sb.toString();
    }

    String name();

    byte value();

    default String row(){
        StringBuilder sb = new StringBuilder();
        sb.append(String.format("| %s | %s |\n", name(), value()));
        return sb.toString();
    }
}
