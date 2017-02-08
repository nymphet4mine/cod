package colourorienteddriver.cod_app.app;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.camera.simplemjpeg.MjpegInputStream;
import com.camera.simplemjpeg.MjpegView;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.URI;
import java.util.regex.Pattern;

public class FernzugriffActivity extends AppCompatActivity {

    private SeekBar seekLenken, seekBeschleunigung;
    private TextView lenkenTV, beschleunigungTV;

    private String ipAdresse;
    private PrintWriter printwriter;
    boolean connected = false;
    Socket client;

    long startTime = 0;

    private int LenkenProgress = 12800, FahrenProgress = 50;

    //Bildübertragung
    private static final boolean DEBUG = false;
    private static final String TAG = "MJPEG";

    private MjpegView mv = null;
    String URL;

    // for settings (network and resolution)
    private static final int REQUEST_SETTINGS = 0;

    private int width = 640;
    private int height = 480;

    private int ip_ad1 = 172;
    private int ip_ad2 = 16;
    private int ip_ad3 = 36;
    private int ip_ad4 = 248;
    private int ip_port = 5005;
    private String ip_command = "?action=stream";

    private boolean suspending = false;

    private Boolean autonomModus = false;

    private Button autonomButton;

    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fernzugriff);

        //Textviews
        lenkenTV = (TextView) findViewById(R.id.textView2);
        beschleunigungTV = (TextView) findViewById(R.id.textView3);


        //seekbars
        seekLenken = (SeekBar) findViewById(R.id.lenken);
        seekBeschleunigung = (SeekBar) findViewById(R.id.beschleunigung);

        //benötigte ip adresse
        ipAdresse = MainActivity.getIp();

        //Startwerte der Seekbars
        seekLenken.setProgress(50);
        seekBeschleunigung.setProgress(50);

        //Button um das autonome Fahren zu de-/aktivieren
        autonomButton = (Button) findViewById(R.id.autonombutton);

        //die Bildübertragung wird im Hintergrund aktiviert
        checkBildmodus(true);

        //setInClickListener um auf den Klick des AF Buttons reagieren zu könnnen
        autonomButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                //Prüfe ob autonomer Modus schon akiviert ist
                if (!autonomModus) {
                    //Autonomer Modus wird aktiviert
                    autonomModus=true;
                    sendToPi(-2);
                    seekLenken.setVisibility(View.INVISIBLE);
                    seekBeschleunigung.setVisibility(View.INVISIBLE);
                    //Toast.makeText(this, "Autonomes Fahren aktiviert", Toast.LENGTH_SHORT).show();
                } else{
                    //Button wurde gedrückt und autonomer Modus ist aktiviert, somit wird er deaktivert
                    sendToPi(-3);
                    autonomModus=false;
                    seekLenken.setVisibility(View.VISIBLE);
                    seekBeschleunigung.setVisibility(View.VISIBLE);
                }
            }
        });

        //AsyncTask für den Verbindungsaufbau sowie versenden der Werte
        new MyAsyncTask(FernzugriffActivity.this).execute(
                ipAdresse,
                "1234",
                String.format("GET / HTTP/1.1\r\nHost: %s\r\n\r\n", ipAdresse));

        startTime = System.currentTimeMillis();
        timerHandler.postDelayed(timerRunnable, 0);

        //Seekbar Lenken
        seekLenken.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {


            //Während dem bewegen der Regler
            @Override
            public void onProgressChanged(SeekBar seekBar, final int progresslenken, boolean fromUser) {

                //LenkenProgess bekommt den aktuellen Wert des Reglers multipliziert mit 256
                LenkenProgress = progresslenken * 256;

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            //Damit beim loslassen der Regler wieder in die Mitte springt
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

                seekLenken.setProgress(50);
            }
        });

        //Seekbar Beschleunigung
        seekBeschleunigung.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            //Während dem bewegen der Regler
            @Override
            public void onProgressChanged(SeekBar seekBar, final int progressbeschleunigung, boolean fromUser) {

                //FahrenProgress bekommt aktuellen Wert des Reglers
                FahrenProgress = progressbeschleunigung;

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            //Regler wird beim loslassen in die Mitte gesetzt
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

                seekBeschleunigung.setProgress(50);


            }

        });


    }

    //Setzt den Client für die Verbindung fest
    void setClient(String ip, int port) throws IOException {

        client = new Socket(ip, port);
    }

    //Gibt Client zurück
    public Socket getClient() {
        return client;
    }

    //Inner Class MyAsyncTask um die Übertragung als Asyncronen Thread auszulagern
    class MyAsyncTask extends AsyncTask<String, Void, String> {

        Activity activity;
        IOException ioException;

        MyAsyncTask(Activity activity) {
            super();
            this.activity = activity;
            this.ioException = null;
        }

        //das Festlegen des Clients geschieht im Hintergrund
        @Override
        protected String doInBackground(String... params) {
            StringBuilder sb = new StringBuilder();

            try {
                setClient(params[0], Integer.parseInt(params[1]));
                connected = true;

            } catch (IOException e) {
                this.ioException = e;

                return "error";
            }

            return "geschafft";
        }

        @Override
        protected void onPostExecute(String result) {
            //Wenn es zu keinen Verbindungsaufbau kommen kann wird Fehler angezeigt
            if (this.ioException != null) {
                new AlertDialog.Builder(this.activity)
                        .setTitle("An error occurrsed")
                        .setMessage(this.ioException.toString())
                        .setIcon(android.R.drawable.ic_dialog_alert)
                        .show();
            }
        }
    }

    //Funktion um Werte an Raspberry Pi zu senden
    public void sendToPi(int message) {
        //Steht die Kommunikation?
        if (connected) {

            try {
                //Erstelle ein Printwriter Objekt mit dem Client
                printwriter = new PrintWriter(getClient().getOutputStream());
            } catch (IOException e) {
                e.printStackTrace();
            }
            //Verschicke die gewünschte message an den Client
            printwriter.write(String.valueOf(Integer.valueOf(message)));
            printwriter.flush();
        }

    }

    //Dient dazu die Übertragung alle 100ms zu vollziehen
    Handler timerHandler = new Handler();
    Runnable timerRunnable = new Runnable() {

        @Override
        public void run() {
            long millis = System.currentTimeMillis() - startTime;
            int seconds = (int) (millis / 1000);
            int minutes = seconds / 60;
            seconds = seconds % 60;

            //Dient dazu um den Button für das Autonome Fahren nur bei den Standartwerten der Regler sichtbar werden zu lassen
            if(FahrenProgress != 50 && LenkenProgress != 12800){

                autonomButton.setVisibility(View.INVISIBLE);
            }else{
                autonomButton.setVisibility(View.VISIBLE);
            }

            //Werte der Lenken- und Fahrenseekbar werden an Raspberry PI versendet
            sendToPi(LenkenProgress + FahrenProgress);

            timerHandler.postDelayed(this, 100);
        }
    };

    public void onDestroy() {

        if (DEBUG) Log.d(TAG, "onDestroy()");


        //-1 wird gesendet um die connection abzubrechen
        sendToPi(-1);

        if (mv != null) {
            mv.freeCameraMemory();
        }

        super.onDestroy();

    }

    public void onResume() {


        if (DEBUG) Log.d(TAG, "onResume()");
        super.onResume();
        if (mv != null) {
            if (suspending) {
                new DoRead().execute(URL);
                suspending = false;
            }
        }


    }

    public void onStart() {
        if (DEBUG) Log.d(TAG, "onStart()");
        super.onStart();
    }

    public void onPause() {
        if (DEBUG) Log.d(TAG, "onPause()");
        super.onPause();
        if (mv != null) {
            if (mv.isStreaming()) {
                mv.stopPlayback();
                suspending = true;
            }
        }
    }

    public void onStop() {
        if (DEBUG) Log.d(TAG, "onStop()");
        super.onStop();
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case REQUEST_SETTINGS:
                if (resultCode == Activity.RESULT_OK) {
                    width = data.getIntExtra("width", width);
                    height = data.getIntExtra("height", height);
                    ip_ad1 = data.getIntExtra("ip_ad1", ip_ad1);
                    ip_ad2 = data.getIntExtra("ip_ad2", ip_ad2);
                    ip_ad3 = data.getIntExtra("ip_ad3", ip_ad3);
                    ip_ad4 = data.getIntExtra("ip_ad4", ip_ad4);
                    ip_port = data.getIntExtra("ip_port", ip_port);
                    ip_command = data.getStringExtra("ip_command");

                    if (mv != null) {
                        mv.setResolution(width, height);
                    }
                    SharedPreferences preferences = getSharedPreferences("SAVED_VALUES", MODE_PRIVATE);
                    SharedPreferences.Editor editor = preferences.edit();
                    editor.putInt("width", width);
                    editor.putInt("height", height);
                    editor.putInt("ip_ad1", ip_ad1);
                    editor.putInt("ip_ad2", ip_ad2);
                    editor.putInt("ip_ad3", ip_ad3);
                    editor.putInt("ip_ad4", ip_ad4);
                    editor.putInt("ip_port", ip_port);
                    editor.putString("ip_command", ip_command);

                    editor.commit();

                    new RestartApp().execute();
                }
                break;
        }
    }

    public class DoRead extends AsyncTask<String, Void, MjpegInputStream> {
        protected MjpegInputStream doInBackground(String... url) {
            //TODO: if camera has authentication deal with it and don't just not work
            HttpResponse res = null;
            DefaultHttpClient httpclient = new DefaultHttpClient();
            HttpParams httpParams = httpclient.getParams();
            HttpConnectionParams.setConnectionTimeout(httpParams, 5 * 1000);
            Log.d(TAG, "1. Sending http request");
            try {
                res = httpclient.execute(new HttpGet(URI.create(url[0])));
                Log.d(TAG, "2. Request finished, status = " + res.getStatusLine().getStatusCode());
                if (res.getStatusLine().getStatusCode() == 401) {
                    //You must turn off camera User Access Control before this will work
                    return null;
                }
                return new MjpegInputStream(res.getEntity().getContent());
            } catch (ClientProtocolException e) {
                e.printStackTrace();
                Log.d(TAG, "Request failed-ClientProtocolException", e);
                //Error connecting to camera
            } catch (IOException e) {
                e.printStackTrace();
                Log.d(TAG, "Request failed-IOException", e);
                //Error connecting to camera
            }
            return null;
        }

        protected void onPostExecute(MjpegInputStream result) {
            mv.setSource(result);
            if (result != null) result.setSkip(1);
            mv.setDisplayMode(MjpegView.SIZE_BEST_FIT);
            mv.showFps(false);
        }
    }

    public class RestartApp extends AsyncTask<Void, Void, Void> {
        protected Void doInBackground(Void... v) {
            FernzugriffActivity.this.finish();
            return null;
        }

        protected void onPostExecute(Void v) {
            startActivity((new Intent(FernzugriffActivity.this, FernzugriffActivity.class)));
        }
    }

    //dient dazu um das Bild in den Hintergrund zu laden
    private void checkBildmodus(boolean modus) {

        try {

            // Starten des asynchronen Tasks und Übergabe der Aktienliste
            if (modus) {

                Toast.makeText(this, "Bildübertragung aktiviert", Toast.LENGTH_SHORT).show();

                String[] ipList = ipAdresse.split(Pattern.quote("."));
                ip_ad1 = Integer.valueOf(ipList[0]);
                ip_ad2 = Integer.valueOf(ipList[1]);
                ip_ad3 = Integer.valueOf(ipList[2]);
                ip_ad4 = Integer.valueOf(ipList[3]);

                StringBuilder sb = new StringBuilder();
                String s_http = "http://";
                String s_dot = ".";
                String s_colon = ":";
                String s_slash = "/";
                sb.append(s_http);
                sb.append(ip_ad1);
                sb.append(s_dot);
                sb.append(ip_ad2);
                sb.append(s_dot);
                sb.append(ip_ad3);
                sb.append(s_dot);
                sb.append(ip_ad4);
                sb.append(s_colon);
                sb.append(ip_port);
                sb.append(s_slash);
                sb.append(ip_command);
                URL = new String(sb);

                mv = (MjpegView) findViewById(R.id.mv);
                if (mv != null) {
                    mv.setResolution(width, height);
                }
                new DoRead().execute(URL);

            } else {
                //Toast.makeText(this, "Bildübertragung nicht aktiviert", Toast.LENGTH_SHORT).show();

            }


        } catch (Exception e) {

            AlertDialog.Builder builder = new AlertDialog.Builder(FernzugriffActivity.this);
            builder.setTitle("An error occurrsed");
            builder.setMessage(e.toString());
            final AlertDialog.Builder builder1 = builder.setIcon(android.R.drawable.ic_dialog_alert);
            final AlertDialog show = builder.show();
        }

    }

}