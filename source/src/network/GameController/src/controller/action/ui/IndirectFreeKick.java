package controller.action.ui;

import data.values.SecondaryGameStates;

/**
 * @author Robert Kessler
 * 
 * This action performs the switch to the Secondary Game State: Free Kick
 * It stops the global clock and prepares the secondary clock to run down to zero
 * When the action is resolved then - the normal clock continues and the previous state
 * is taken again. Based on which side the action is executed for the FreeKick Mode in the
 * Secondary State Object is updated
 */
public class IndirectFreeKick extends GameInterruption
{
    public IndirectFreeKick(int side)
    {
        super(side, SecondaryGameStates.INDIRECT_FREEKICK);
    }
}