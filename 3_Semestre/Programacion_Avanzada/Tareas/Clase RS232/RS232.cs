using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Clase_RS232
{
    public partial class RS232 : Form
    {
        string[] Ports = new string[5];
        string ActualPort;

        public RS232()
        {
            InitializeComponent();
        }

        private void Button_Search_Click(object sender, EventArgs e)
        {
            Ports = SerialPort.GetPortNames();
            comboBox_SP.Items.Clear();
            comboBox_SP.Items.AddRange(Ports);
        }

        private void RS232_Load(object sender, EventArgs e)
        {

        }
    }
}
