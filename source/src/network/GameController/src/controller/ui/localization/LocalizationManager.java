package controller.ui.localization;

/**
 * Created by rkessler on 2017-03-23.
 */
public class LocalizationManager {

    private static LocalizationManager _instance = null;

    public static LocalizationManager getInstance(){
        if (_instance == null){
            _instance = new LocalizationManager();
        }
        return _instance;
    }

    public static Localization getLocalization(){
        if (_instance == null){
            _instance = new LocalizationManager();
        }
        return _instance.currentLocalization;
    }

    private Localization currentLocalization;

    private LocalizationManager(){
        this.currentLocalization = new Localization();
    }
}
