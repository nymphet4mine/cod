package colourorienteddriver.cod_app.app;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


/**
 * Created by AlexR on 26.10.2016.
 */

public class SettingsActivity extends AppCompatActivity {
    Button save;
    EditText text;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        save = (Button) findViewById(R.id.saveButton);
        save.setOnClickListener(saveHandler);
        text = (EditText) findViewById(R.id.editText);
    }

    View.OnClickListener saveHandler = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            String ipAdresse = text.getText().toString();
            MainActivity.setIp(ipAdresse);
            Intent myIntent = new Intent(v.getContext(), MainActivity.class);
            startActivityForResult(myIntent, 0);

        }
    };


}
