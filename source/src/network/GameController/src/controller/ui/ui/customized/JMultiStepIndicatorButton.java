package controller.ui.ui.customized;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

/**
 * A button that has a little indicator like a progress bar
 * Created by rkessler on 2017-07-16.
 */
public class JMultiStepIndicatorButton extends Button {


    private int _maxSteps;
    private int _currentStep;

    public JMultiStepIndicatorButton(String caption, int steps) {
        super(caption);
        setContentAreaFilled(false);
        setFocusPainted(false); // used for demonstration

        _currentStep = 0;
        _maxSteps = steps;
    }

    public JMultiStepIndicatorButton() {
        super("");
        setContentAreaFilled(false);
        setFocusPainted(false); // used for demonstration

        _currentStep = 0;
        _maxSteps = 1;
    }

    public void setStep(int step){
        this._currentStep = step;
    }

    @Override
    protected void paintComponent(Graphics g) {
        Graphics2D g2 = (Graphics2D) g.create();

        if (this.isEnabled()) {
            g2.setPaint(new GradientPaint(new Point(0, 0), new Color(238, 244, 249), new Point(0, getHeight()), new Color(190, 211, 231)));
            g2.fillRect(0, 0, getWidth(), getHeight());


            int bar_height = (int) (getHeight() / 6.0);
            int element_width = getWidth() / _maxSteps;

            for (int i = 0; i <= _maxSteps; i++) {

                Color useColor = Color.white;
                if (i < _currentStep) {
                    useColor = new Color(41, 160, 41);
                }

                g2.setColor(useColor);
                int x = i * element_width;

                g2.fillRect(x, getHeight() - bar_height, element_width, bar_height);
            }
            g2.dispose();
        }

        super.paintComponent(g);
    }


}
