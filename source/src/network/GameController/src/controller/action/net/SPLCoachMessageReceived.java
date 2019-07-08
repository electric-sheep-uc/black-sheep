package controller.action.net;

import controller.action.ActionType;
import controller.action.GCAction;
import controller.net.RobotWatcher;
import data.states.AdvancedData;
import data.spl.SPLCoachMessage;
import data.values.Penalties;

public class SPLCoachMessageReceived extends GCAction
{
    private SPLCoachMessage message;
    
    public SPLCoachMessageReceived(SPLCoachMessage message)
    {
        super(ActionType.NET);
        this.message = message;
    }
    
    @Override
    public void perform(AdvancedData data)
    {
        System.out.println("Remove me i am useless");
    }

    @Override
    public boolean isLegal(AdvancedData data)
    {
        return true;
    }

}
