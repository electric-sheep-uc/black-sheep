package controller.ui.ui.components;

import data.states.AdvancedData;
import data.values.Penalties;

import javax.swing.*;
import java.awt.*;

/**
 * Created by rkessler on 2017-03-27.
 */
public abstract class AbstractComponent extends JPanel {

    private static final Color COLOR_HIGHLIGHT = Color.YELLOW;
    private static final Color COLOR_STANDARD = (new JButton()).getBackground();
    private static final boolean IS_OSX = System.getProperty("os.name").contains("OS X");

    /**
     * Set the given button highlighted or normal.
     *
     * @param button        The button to highlight.
     * @param highlight     If the button should be highlighted.
     */
    void highlight(AbstractButton button, boolean highlight)
    {
        button.setBackground(highlight ? COLOR_HIGHLIGHT : COLOR_STANDARD);
        if (IS_OSX) {
            button.setOpaque(highlight);
            button.setBorderPainted(!highlight);
        }
    }

    void highlight(AbstractButton button)
    {
        if (button.getBackground() == COLOR_STANDARD){
            button.setBackground(COLOR_HIGHLIGHT);
        } else {
            button.setBackground(COLOR_STANDARD);
        }
    }

    void resetHighlighting(AbstractButton button){
        button.setBackground(COLOR_STANDARD);
    }

    public abstract void update(AdvancedData data);

}
