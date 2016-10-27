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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button fernzugriff = (Button) findViewById(R.id.fernzugriff);
        fernzugriff.setOnClickListener(fernzugriffHandler);
        Button bildübertragung = (Button) findViewById(R.id.bildübertragung);
        bildübertragung.setOnClickListener(bildübertragungHandler);
    }

    View.OnClickListener fernzugriffHandler = new View.OnClickListener() {
        @Override
        public void onClick(View v) {

            Intent myIntent = new Intent(v.getContext(), FernzugriffActivity.class);
            startActivityForResult(myIntent, 0);

        }
    };

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

    @Override
    public boolean onOptionsItemSelected(MenuItem item){
        int id = item.getItemId();
        if(id == R.id.settings){
            Intent intent = new Intent(this, SettingsActivity.class);
            startActivity(intent);
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public static String getIp (){
        return ip;
    }

    public static void setIp (String ipAdresse) {
        ip = ipAdresse;
    }


}
