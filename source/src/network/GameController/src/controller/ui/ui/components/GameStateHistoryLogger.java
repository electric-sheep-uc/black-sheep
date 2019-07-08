package controller.ui.ui.components;

import common.Log;
import common.TotalScaleLayout;
import controller.EventHandler;
import controller.action.ActionBoard;
import controller.action.GCAction;
import controller.ui.ui.customized.ToggleButton;
import controller.ui.ui.customized.Button;
import data.states.AdvancedData;

import javax.swing.*;
import java.awt.*;

/**
 * Created by rkessler on 2017-03-31.
 */
public class GameStateHistoryLogger extends AbstractComponent {

    protected static final String CANCEL = "Cancel";

    protected JToggleButton[] undo;
    protected JButton cancelUndo;
    protected JPanel log;

    public GameStateHistoryLogger(){
        defineLayout();
    }

    public void defineLayout(){
        log = new JPanel();

        TotalScaleLayout layout = new TotalScaleLayout(log);
        log.setLayout(layout);

        int undoButtonCount = ActionBoard.MAX_NUM_UNDOS_AT_ONCE-1;
        float elementWidth = (float) (1.0 / (1 + undoButtonCount));
        float cancelWidth = (float) (0.75 * elementWidth);

        undo = new JToggleButton[undoButtonCount];

        for (int i=0; i < undo.length; i++) {
            undo[i] = new ToggleButton();
            undo[i].setVisible(false);
            undo[i].addActionListener(ActionBoard.undo[i+1]);
            layout.add(1-elementWidth-cancelWidth-i*elementWidth, 0, elementWidth, 1, undo[i]);
        }

        cancelUndo = new Button(CANCEL);
        cancelUndo.setVisible(false);
        cancelUndo.addActionListener(ActionBoard.cancelUndo);
        layout.add(1-cancelWidth, 0, cancelWidth, 1, cancelUndo);


        log.setVisible(true);
        this.setLayout(new TotalScaleLayout(this));
        ((TotalScaleLayout) this.getLayout()).add(0, 0, 1, 1, log);

        this.setVisible(true);
    }

    @SuppressWarnings("Duplicates")
    @Override
    public void update(AdvancedData data) {
        GCAction highlightEvent = EventHandler.getInstance().lastUIEvent;
        String[] undos = Log.getLast(ActionBoard.MAX_NUM_UNDOS_AT_ONCE);
        boolean undoFromHere = false;
        for (int i=undo.length - 1; i >= 0; i--) {
            undo[i].setVisible(!undos[i].equals(""));
            undo[i].setEnabled(!undos[i].contains(" vs "));
            if ((highlightEvent == ActionBoard.undo[i+1]) && (!ActionBoard.undo[i+1].executed)) {
                undoFromHere = true;
            }
            if (undoFromHere) {
                undo[i].setText("<html><center>Undo '"+undos[i] + "\'?");
                undo[i].setSelected(true);
            } else {
                undo[i].setText("<html><center>"+undos[i]);
                undo[i].setSelected(false);
            }
        }
        cancelUndo.setVisible(undoFromHere);
    }
}
