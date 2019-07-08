package controller.ui.ui;

import controller.Clock;
import controller.ui.GCGUI;
import controller.ui.ui.components.AbstractComponent;
import data.states.AdvancedData;
import data.states.GamePreparationData;

import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.List;

/**
 * A modern extensible component based UI system which can be extended with elements
 */
public abstract class AbstractUI extends JFrame implements GCGUI {

    protected List<AbstractComponent> elementsReceivingUpdates;
    protected AdvancedData initialData;
    protected GamePreparationData gamePrepData;

    public AbstractUI(boolean fullscreen, AdvancedData initialData, GamePreparationData gamePrepData){
        super("GameController");

        elementsReceivingUpdates = new ArrayList<>();
        this.initialData = initialData;
        this.gamePrepData = gamePrepData;

        addWindowListener(new WindowAdapter()
        {
            @Override
            public void windowClosing(WindowEvent e) {
                Clock.getInstance().interrupt();
                dispose();
            }
        });
    }

    @Override
    public void update(AdvancedData data) {
        for(AbstractComponent uiPart : elementsReceivingUpdates){
            uiPart.update(data);
        }
        repaint();
    }
}
