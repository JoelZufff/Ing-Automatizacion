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
        // DataTable para tabla dinamica
        DataTable OrdenDataTable = new DataTable();

        // Variables Globales
        public bool ConectionStatus = false;
        public bool PendingOrder = false;

        public int ComputerWireReel = 0;
        public int WireReel = 0;

        string[] Ports;
        public int PortsIndex;

        public Main()
        {
            InitializeComponent();
            OrderDataGridView.Show();
            OrderDataGridView.DataSource = OrdenDataTable;
        }

        private void Main_Load(object sender, EventArgs e)
        {
            OrdenDataTable.Columns.Add("Cantidad", typeof(string));
            OrdenDataTable.Columns.Add("Longitud", typeof(string));
            OrdenDataTable.Columns.Add("Pelado", typeof(string));

            ConectionButton_Click(sender, e);
        }

        private void ConectionTimer_Tick(object sender, EventArgs e)
        {
            // Intentar conexion con wire trimmer con puertos disponibles

            if (ConectionStatus && SerialPort.IsOpen)        // Si ya hubo conexion
            {
                ConectionTimer.Enabled = false;             // Desactivamos temporizador

                ConectionPanel.Visible = false;
                WireOrderPanel.Visible = true;

                // Configuramos valores de WireOrder
                ReelLabel.Text = WireReel.ToString();

                if (WireReel > 30)
                    AddButton.Enabled = true;

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

                    // Enviamos caracter de conexion
                    SerialPort.Write("+");
                }
                catch (Exception ex) { }
            }
            else                                            // Si ya se probaron todos los puertos
            {
                ConectionTimer.Enabled = false;             // Desactivamos temporizador
                MessageBox.Show("Conexion Fallida", "Wire-Trimmer", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                        WireReel = int.Parse(SerialPort.ReadLine());
                        ConectionStatus = true;
                    }
                    break;
                case '*':   // Caracter de orden finalizada
                    {
                        PendingOrder = false;
                        SerialPort.Write("+");      // Reafirmamos conexion
                    }
                    break;
            }
        }

        private void PrintButton_Click(object sender, EventArgs e)
        {
            DialogResult Answer = MessageBox.Show("¿Comenzar Impresion?", "Confirmacion", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);
            if (Answer == DialogResult.No)
                return;

            // Activamos timer para envio de ordenes
            OrderTimer.Enabled = true;
        }

        private void Agregar_Click(object sender, EventArgs e)
        {
            // Agregamos orden a table de ordenes
            OrdenDataTable.Rows.Add(Amount.Value, Length.Value, PeelingLength.Value);

            WireReel -= (int) (Amount.Value * (2 * PeelingLength.Value + Length.Value));
            ReelLabel.Text = WireReel.ToString();

            // Reiniciamos valores
            Amount.Value = 1;
            Length.Value = 10;
            PeelingLength.Value = 5;

            EraseButton.Enabled = true;
            PrintButton.Enabled = true;
            
            if(WireReel < 30)
                AddButton.Enabled = false;
        }

        private void Eliminar_Click(object sender, EventArgs e)
        {
            DialogResult Answer = MessageBox.Show("¿Esta seguro que desea eliminar la orden seleccionada?", "Confirmacion", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);
            if (Answer == DialogResult.No)
                return;

            int Index = OrderDataGridView.CurrentRow.Index;

            int Amount = int.Parse(OrdenDataTable.Rows[Index][0].ToString());
            int Length = int.Parse(OrdenDataTable.Rows[Index][1].ToString());
            int PeelingLength = int.Parse(OrdenDataTable.Rows[Index][2].ToString());
            
            WireReel += Amount * (2 * PeelingLength + Length);
            ReelLabel.Text = WireReel.ToString();
            
            OrdenDataTable.Rows[Index].Delete();

            if (OrdenDataTable.Rows.Count == 0)
            {
                EraseButton.Enabled = false;
                PrintButton.Enabled = false;
            }

            if(WireReel > 30)
                AddButton.Enabled = true;
        }

        // Configuracion de valores maximos
        private void Length_Click(object sender, EventArgs e)
        {
            Length.Maximum = WireReel / Amount.Value - 2 * PeelingLength.Value;
        }

        private void Amount_Click(object sender, EventArgs e)
        {
            Amount.Maximum = WireReel / (Length.Value + 2 * PeelingLength.Value);
        }

        private void PeelingLength_Click(object sender, EventArgs e)
        {
            Length_Click(sender, e);
            Length.Validate();
        }

        private void Main_FormClosed(object sender, FormClosedEventArgs e)
        {
            // Mandar caracter de desconexion a PIC
            if (SerialPort.IsOpen)
            {
                SerialPort.Write("-");      // Enviamos caracter de desconexion
                SerialPort.Close();
            }
        }

        private void OrderTimer_Tick(object sender, EventArgs e)
        {   
            if (OrdenDataTable.Rows.Count == 0)         // Ya no hay ordenes pendientes
            {
                OrderTimer.Enabled = false;
                return;
            }

            if (PendingOrder == false)     // Si no hay impresion pendiente
            {
                int Amount          = int.Parse(OrdenDataTable.Rows[0][0].ToString());
                int Length          = int.Parse(OrdenDataTable.Rows[0][1].ToString());
                int PeelingLength   = int.Parse(OrdenDataTable.Rows[0][2].ToString());

                SerialPort.Write('*' + $"{Amount:D4}" + $"{Length:D5}" + $"{PeelingLength:D2}");
                PendingOrder = true;

                // Elmiminamos la fila
                OrdenDataTable.Rows[0].Delete();
            }
        }
    }
}