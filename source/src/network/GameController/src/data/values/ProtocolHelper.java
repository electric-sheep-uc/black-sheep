package data.values;

import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;

import java.util.List;

/**
 * This class helps to generate the file that can be added to the Wiki such that a team doesn't need to look
 * into the Java code to see the allowed values for specific data types defined in Enums
 */
public class ProtocolHelper {

    public static void main(String[] args) throws IOException, NoSuchMethodException, IllegalAccessException, InvocationTargetException {
        new ProtocolHelper();
    }

    ProtocolHelper() throws IOException, NoSuchMethodException, InvocationTargetException, IllegalAccessException {
        FileWriter fw = new FileWriter("protocol_appendix.html");

        List<Class> enumList = new ArrayList<Class>();
        enumList.add(GameStates.class);
        enumList.add(GameTypes.class);
        enumList.add(Penalties.class);
        enumList.add(PlayerResponses.class);
        enumList.add(SecondaryGameStates.class);
        enumList.add(TeamColors.class);

        for(Class c: enumList){
            Method row = c.getMethod("row");
            Method header = c.getMethod("header");
            StringBuilder sb = new StringBuilder();
            sb.append("###");
            sb.append(c.getSimpleName());
            sb.append("\n");
            sb.append(header.invoke(c.getEnumConstants()[0]));
            for(Object o : c.getEnumConstants()){
                sb.append(row.invoke(o));
            }
            sb.append("\n\n");
            fw.append(sb.toString());
        }

        fw.close();
    }
}
