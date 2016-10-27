package colourorienteddriver.cod_app.app;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.VideoView;

/**
 * Created by AlexR on 26.10.2016.
 */

public class BilduebertragungsActivity extends Activity {
    String vidAdress = "http://192.168.0.12:8090";

    //String vidAdress = "https://archive.org/download/ksnn_compilation_master_the_internet/ksnn_compilation_master_the_internet_512kb.mp4";
    Uri vidUri = Uri.parse(vidAdress);

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bilduebertragung);
        VideoView vidView = (VideoView)findViewById(R.id.videoView);
        vidView.setVideoURI(vidUri);
        try {
            vidView.start();
        }catch (Exception e){
            
        }

    }
}
