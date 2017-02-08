package colourorienteddriver.cod_app.app;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;


public class MainActivity extends AppCompatActivity {

    private static String ip;

    private Button fernzugriff;
    private Button bildübertragung;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Button für die Fernsteuerung
        fernzugriff = (Button) findViewById(R.id.fernzugriff);
        fernzugriff.setOnClickListener(fernzugriffHandler);

        //Button für die Bildübertragung
        bildübertragung = (Button) findViewById(R.id.bildübertragung);
        bildübertragung.setOnClickListener(bildübertragungHandler);

    }

    //OnClickLitener um auf den Druck des Buttons zu reagieren
    View.OnClickListener fernzugriffHandler = new View.OnClickListener() {
        @Override
        public void onClick(View v) {

            Intent myIntent = new Intent(v.getContext(), FernzugriffActivity.class);
            startActivityForResult(myIntent, 0);

        }
    };

    //OnClickLitener um auf den Druck des Buttons zu reagieren
    View.OnClickListener bildübertragungHandler = new View.OnClickListener() {
        @Override
        public void onClick(View v) {

            Intent myIntent = new Intent(v.getContext(), BilduebertragungsActivity.class);
            startActivityForResult(myIntent, 0);

        }
    };


    @Override
    public boolean onCreateOptionsMenu (Menu menu){
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    //Methode um das Settingssymbol bzw. die Settings rechts oben im Bildschirm anzeigen zu lassen
    @Override
    public boolean onOptionsItemSelected(MenuItem item){
        int id = item.getItemId();
        if(id == R.id.settings){

            //Starte die MyPreferenceActiviy Klasse
            Intent intent = new Intent(this, MyPreferenceActivity.class);
            startActivity(intent);

           return true;
        }
        return super.onOptionsItemSelected(item);
    }

    //Get Methode für die IP
    public static String getIp (){
        return ip;
    }

    //Setzt die Ip fest
    public static void setIp (String ipAdresse) {
        ip = ipAdresse;
    }

    public void onDestroy() {

        //-1 wird gesendet um die connection abzubrechen
        FernzugriffActivity fa = new FernzugriffActivity();
                fa.sendToPi(-1);

        super.onDestroy();

    }



}
