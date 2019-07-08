package controller.ui.gameplay;

import data.states.AdvancedData;

/**
 * Created by rkessler on 2017-03-23.
 */
public interface CommonGUI {

    void setupGuiElement();

    void setupLayout();

    void setupActionHandlers();

    void update(AdvancedData data);

    void dispose();
}