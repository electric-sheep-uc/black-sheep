package controller.ui.ui.customized;


/**
 * @author Ludovic Hofer
 *
 * This class allows to represents the button for all the game interruptions which behaves similarly such as:
 * - Penalty Kick
 * - Direct Free Kick
 * - Indirect Free Kick
 *
 * Soon to be introduced
 * - Corner Kick
 * - Goal Kick
 * - Throw-in
 */
public class GameInterruptionButton extends JMultiStepIndicatorButton  {

    public GameInterruptionButton(String caption) {
        super(caption, 3);
        base_message = caption;
    }

    public void setSubMode(byte subMode) {
        switch(subMode){
            case 0:
                setText(base_message + ": Start placing");
                setStep(1);
                break;
            case 1:
                setText(base_message + ": End placing");
                setStep(2);
                break;
            case 2:
                setText(base_message + ": Execute");
                setStep(3);
                break;
        }
    }

    public void setInitialMode() {
        setText(base_message);
        setStep(0);
    }

    private String base_message;
}
