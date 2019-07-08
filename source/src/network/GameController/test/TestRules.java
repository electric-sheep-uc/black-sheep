import data.Rules;
import data.hl.HL;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.assertTrue;

public class TestRules {

    @BeforeClass
    public static void setUp(){
        System.setProperty("CONFIG_ROOT", "test_resources/");
    }

    @Test
    public void test_rules_are_equal_with_casting() {
        Rules spl_rules1 = new HL();
        Rules spl_rules2 = new HL();

        assertTrue(spl_rules1.equals(spl_rules2));
        assertTrue(spl_rules2.equals(spl_rules1));
    }

}
