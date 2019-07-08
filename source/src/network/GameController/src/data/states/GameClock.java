package data.states;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by rkessler on 2017-03-23.
 */
public class GameClock implements Serializable {

    List<ExtraClock> _extraClocks = new ArrayList<>();

    private ExtraClock secondaryClock;

    public void addExtraClock(String label, int lifetime){
        _extraClocks.add(new ExtraClock(label, lifetime));
    }

    public List<ExtraClock>  getExtraClocks(){
        for (ExtraClock e: _extraClocks){
            if (e.isLowerThan(0)){
                _extraClocks.remove(e);
            }
        }
        return _extraClocks;
    }

    public Integer getSecondaryTime() {
        if (secondaryClock == null){
            return null;
        } else {
            return secondaryClock.getRemainingSeconds();
        }
    }

    public void setSecondaryClock(int time_in_seconds){
        secondaryClock = new ExtraClock(time_in_seconds);
    }

    public void clearSecondaryClock(){
        secondaryClock = null;
    }


    public boolean isSecondaryClockLowerThan(Integer value) {
       return secondaryClock != null && secondaryClock.isLowerThan(value);
    }

}
