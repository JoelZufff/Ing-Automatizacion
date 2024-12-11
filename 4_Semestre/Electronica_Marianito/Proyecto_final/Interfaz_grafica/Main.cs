using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Wire_Trimmer
{
    public partial class Main : Form
    {
        // Variables Globales
        public bool CON_status = false;

        // Variables de conexion UART
        string[] Ports;
        public int PortsIndex;

        string X_temp_string;
        string THETA_temp_string;
        string RX_string;

        public Main()
        {
            InitializeComponent();
        }

        private void Main_Load(object sender, EventArgs e)
        {
            ConectionButton_Click(sender, e);
        }

        private void ConectionTimer_Tick(object sender, EventArgs e)
        {
            // Intentar conexion con wire trimmer con puertos disponibles

            if (CON_status && SerialPort.IsOpen)        // Si ya hubo conexion
            {
                ConectionTimer.Enabled = false;             // Desactivamos temporizador

                ConectionPanel.Visible = false;
                Control_Panel.Visible = true;

                return;
            }

            if (SerialPort.IsOpen)                      // Si no hubo conexion y hay un puerto abierto
                SerialPort.Close();

            if (PortsIndex >= 0)
            {
                ConectionProgressBar.Value = Ports.Length - PortsIndex;

                SerialPort.GetType();

                try
                {
                    SerialPort.PortName = Ports[PortsIndex--];
                    SerialPort.Open();
                }
                catch (Exception ex) { }
            }
            else                                            // Si ya se probaron todos los puertos
            {
                ConectionTimer.Enabled = false;             // Desactivamos temporizador
                MessageBox.Show("Conexion Fallida", "Grua de 3 ejes", MessageBoxButtons.OK, MessageBoxIcon.Error);
                ConectionButton.Enabled = true;
            }
        }

        private void ConectionButton_Click(object sender, EventArgs e)
        {
            Ports = SerialPort.GetPortNames();

            if (Ports.Length > 0)
            {
                PortsIndex = Ports.Length - 1;
                ConectionProgressBar.Maximum = Ports.Length;
                ConectionProgressBar.Value = 0;
                ConectionButton.Enabled = false;

                // Iniciamos temporizador para conexion
                ConectionTimer.Enabled = true;
            }
            else
                MessageBox.Show("No hay dispositivos conectados", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            char data = (char)SerialPort.ReadChar();

            // Analizo el caracter recibido
            switch (data)
            {
                case '+':   // Caracter de conexion
                {
                    CON_status = true;

                    // Almacenamos variables recibidas
                    X_temp_string = SerialPort.ReadLine() + "° C";                     // Temperatura de motor 1
                    THETA_temp_string = SerialPort.ReadLine() + "° C";                     // Temperatura de motor
                    SerialPort.Write("+");          // Devolvemos confirmacion de 
                    
                    break;
                }
                case '#':
                {
                    RX_string = SerialPort.ReadLine();
                    break;
                }
            }
        }

        private void Main_FormClosed(object sender, FormClosedEventArgs e)
        {
            // Mandar caracter de desconexion a PIC
            if (SerialPort.IsOpen)
                SerialPort.Close();
        }

        private void Send_Click(object sender, EventArgs e)
        {
            DialogResult Answer = MessageBox.Show("¿Enviar instrucciones?", "Confirmacion", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);
            if (Answer == DialogResult.No)
                return;

            try
            {
                SerialPort.Write("*" + X_number.Value.ToString() + "\r" + (X_dir.Checked ? "1" : "0") + Z_number.Value.ToString() + "\r" + (Z_dir.Checked ? "1" : "0") + Theta_number.Value.ToString() + "\r" + (Theta_dir.Checked ? "1" : "0"));
            }
            catch
            {
                SerialPort.Close();
                return;
            }

            X_number.Value = Z_number.Value = Theta_number.Value = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            RX_text.Text = RX_string;
            Temp1.Text = X_temp_string;
            Temp2.Text = THETA_temp_string;
        }
    }
}