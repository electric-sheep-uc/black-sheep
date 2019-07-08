package controller.ui.ui.customized;

import controller.ui.gameplay.GUI;

import javax.swing.*;

/**
 * Created by rkessler on 2017-03-30.
 */
public class Button extends JButton
{
    protected static final long serialVersionUID = -1533689100759569853L;

    public static final String BUTTON_MASK = GUI.IS_APPLE_JAVA
            ? "<html><div style=\"padding: 0px 12px\"><center>%s</center></div></html>"
            : "<html><center>%s</center></html>";

    public Button()
    {
        setMargin(GUI.insets);
    }

    public Button(String text)
    {
        setMargin(GUI.insets);
        setText(text);
    }

    public void setText(String text)
    {
        super.setText(String.format(BUTTON_MASK, text));
    }
}


