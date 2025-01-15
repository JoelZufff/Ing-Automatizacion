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
using System.Windows.Forms.VisualStyles;

namespace Wire_Trimmer
{
    public partial class Main : Form
    {
        // Variables Globales
        public bool CON_status = false;

        // Variables de conexion UART
        string[] Ports;
        public int PortsIndex;

        public bool New_Data = false;

        public string TEMP;
        public string NS_CAR_FLOW;
        public string SN_CAR_FLOW;
        public string EW_CAR_FLOW;
        public string WE_CAR_FLOW;
        public string PTL_DIST;


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
                    TEMP = SerialPort.ReadLine();
                    NS_CAR_FLOW = SerialPort.ReadLine();
                    SN_CAR_FLOW = SerialPort.ReadLine();
                    EW_CAR_FLOW = SerialPort.ReadLine();
                    WE_CAR_FLOW = SerialPort.ReadLine();
                    PTL_DIST = SerialPort.ReadLine();

                    New_Data = true;

                    break;
                }
            }
        }

        private void Main_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (SerialPort.IsOpen)
                SerialPort.Close();
        }

        private void Act_variables_Tick(object sender, EventArgs e)
        {
            // Actualizamos variables mostradas
            if (New_Data)
            {
                TEMP_num.Value = int.Parse(TEMP);
                NS.Value = int.Parse(NS_CAR_FLOW);
                SN.Value = int.Parse(SN_CAR_FLOW);
                EW.Value = int.Parse(EW_CAR_FLOW);
                WE.Value = int.Parse(WE_CAR_FLOW);
                PTL.Value = int.Parse(PTL_DIST);
            }
        }
    }
}