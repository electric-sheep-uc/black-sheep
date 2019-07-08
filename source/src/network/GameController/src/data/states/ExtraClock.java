package data.states;

import java.io.Serializable;

public class ExtraClock implements Serializable {

    private long start_time;
    private int life_time;
    private String label;

    public ExtraClock(String label, int lifetime) {
        this.start_time = System.currentTimeMillis();
        this.life_time = lifetime;
        this.label = label;
    }

    public ExtraClock(int lifetime) {
        this.start_time = System.currentTimeMillis();
        this.life_time = lifetime;
        this.label = "Secondary Clock";
    }

    public int getRemainingSeconds() {
        return life_time - getSecondsSince(start_time);
    }

    public boolean isLowerThan(Integer value) {
        return getRemainingSeconds() <= value;
    }

    public int getSecondsSince(long millis) {
        return millis == 0 ? 100000 : (int) (getTime() - millis) / 1000;
    }

    public long getTime() {
        return System.currentTimeMillis();
    }

    public String getLabel(){
        return this.label;
    }

}
