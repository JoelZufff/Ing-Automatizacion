namespace Sistema_Almacen
{
    partial class RegistroCliente
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.RegExp = new System.Windows.Forms.TextBox();
            this.Expediente = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.RegTel = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.RegName = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.Registrar = new System.Windows.Forms.Button();
            this.RegCarr = new System.Windows.Forms.ComboBox();
            this.RegStatus = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // RegExp
            // 
            this.RegExp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.RegExp.BackColor = System.Drawing.SystemColors.Window;
            this.RegExp.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RegExp.Location = new System.Drawing.Point(168, 91);
            this.RegExp.MaxLength = 6;
            this.RegExp.Name = "RegExp";
            this.RegExp.Size = new System.Drawing.Size(151, 24);
            this.RegExp.TabIndex = 0;
            this.RegExp.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.RegExp_KeyPress);
            // 
            // Expediente
            // 
            this.Expediente.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.Expediente.AutoSize = true;
            this.Expediente.Font = new System.Drawing.Font("Franklin Gothic Book", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Expediente.Location = new System.Drawing.Point(49, 91);
            this.Expediente.Name = "Expediente";
            this.Expediente.Size = new System.Drawing.Size(94, 21);
            this.Expediente.TabIndex = 1;
            this.Expediente.Text = "Expediente :";
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Franklin Gothic Book", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(49, 146);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 21);
            this.label1.TabIndex = 2;
            this.label1.Text = "Nombre :";
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Franklin Gothic Book", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(49, 211);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 21);
            this.label2.TabIndex = 4;
            this.label2.Text = "Telefono :";
            // 
            // RegTel
            // 
            this.RegTel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.RegTel.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RegTel.Location = new System.Drawing.Point(168, 211);
            this.RegTel.MaxLength = 10;
            this.RegTel.Name = "RegTel";
            this.RegTel.Size = new System.Drawing.Size(153, 24);
            this.RegTel.TabIndex = 5;
            this.RegTel.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.RegTel_KeyPress);
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Franklin Gothic Book", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(49, 271);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(66, 21);
            this.label3.TabIndex = 6;
            this.label3.Text = "Carrera :";
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Franklin Gothic Book", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(52, 325);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(68, 21);
            this.label4.TabIndex = 7;
            this.label4.Text = "Estatus :";
            // 
            // RegName
            // 
            this.RegName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.RegName.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RegName.Location = new System.Drawing.Point(168, 146);
            this.RegName.Name = "RegName";
            this.RegName.Size = new System.Drawing.Size(256, 24);
            this.RegName.TabIndex = 8;
            this.RegName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox1_KeyPress);
            // 
            // label5
            // 
            this.label5.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.label5.Font = new System.Drawing.Font("Franklin Gothic Medium Cond", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.Color.Black;
            this.label5.Location = new System.Drawing.Point(161, 19);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(149, 41);
            this.label5.TabIndex = 10;
            this.label5.Text = "REGISTRO";
            // 
            // Registrar
            // 
            this.Registrar.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.Registrar.Font = new System.Drawing.Font("Franklin Gothic Book", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Registrar.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Registrar.Location = new System.Drawing.Point(152, 393);
            this.Registrar.Name = "Registrar";
            this.Registrar.Size = new System.Drawing.Size(159, 43);
            this.Registrar.TabIndex = 11;
            this.Registrar.Text = "Registrar";
            this.Registrar.UseVisualStyleBackColor = true;
            this.Registrar.Click += new System.EventHandler(this.Registrar_Click);
            // 
            // RegCarr
            // 
            this.RegCarr.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.RegCarr.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.RegCarr.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.CustomSource;
            this.RegCarr.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RegCarr.FormattingEnabled = true;
            this.RegCarr.Items.AddRange(new object[] {
            "Ingenieria en Mecanica y Automotriz",
            "Ingenieria Fisica",
            "Ingenieria Agroindustrial",
            "Ingenieria Civil",
            "Ingenieria Industrial y Manufactura",
            "Ingenieria Electromecanica",
            "Ingenieria en Automatizacion",
            "Ingenieria en Nanotecnologia",
            "Ingenieria Biomedica",
            "Licenciatura en Matematicas Aplicadas",
            "Licenciatura en Diseno Industrial",
            "Licenciatura en Arquitectura",
            "Licenciatura en Animacion Digital"});
            this.RegCarr.Location = new System.Drawing.Point(168, 269);
            this.RegCarr.Name = "RegCarr";
            this.RegCarr.Size = new System.Drawing.Size(263, 26);
            this.RegCarr.TabIndex = 12;
            // 
            // RegStatus
            // 
            this.RegStatus.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.RegStatus.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.RegStatus.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.CustomSource;
            this.RegStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RegStatus.FormattingEnabled = true;
            this.RegStatus.Items.AddRange(new object[] {
            "Estudiante",
            "Profesor"});
            this.RegStatus.Location = new System.Drawing.Point(168, 324);
            this.RegStatus.Name = "RegStatus";
            this.RegStatus.Size = new System.Drawing.Size(152, 26);
            this.RegStatus.TabIndex = 13;
            // 
            // Registro
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(464, 461);
            this.Controls.Add(this.RegStatus);
            this.Controls.Add(this.RegCarr);
            this.Controls.Add(this.Registrar);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.RegName);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.RegTel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Expediente);
            this.Controls.Add(this.RegExp);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MinimumSize = new System.Drawing.Size(480, 500);
            this.Name = "Registro";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = " ";
            this.Load += new System.EventHandler(this.Registro_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox RegExp;
        private System.Windows.Forms.Label Expediente;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox RegTel;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox RegName;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button Registrar;
        private System.Windows.Forms.ComboBox RegCarr;
        private System.Windows.Forms.ComboBox RegStatus;
    }
}