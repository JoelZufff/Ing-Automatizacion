namespace Sistema_Almacen
{
    partial class Principal
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.TextBoxExp = new System.Windows.Forms.TextBox();
            this.TitleEXP = new System.Windows.Forms.Label();
            this.SendButton = new System.Windows.Forms.Button();
            this.AdminButton = new System.Windows.Forms.Button();
            this.RegistLabel = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // TextBoxExp
            // 
            this.TextBoxExp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.TextBoxExp.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBoxExp.Location = new System.Drawing.Point(130, 126);
            this.TextBoxExp.MaxLength = 6;
            this.TextBoxExp.Name = "TextBoxExp";
            this.TextBoxExp.Size = new System.Drawing.Size(269, 31);
            this.TextBoxExp.TabIndex = 0;
            this.TextBoxExp.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.getEXP_KeyPress);
            // 
            // TitleEXP
            // 
            this.TitleEXP.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.TitleEXP.AutoSize = true;
            this.TitleEXP.Font = new System.Drawing.Font("Franklin Gothic Medium Cond", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TitleEXP.Location = new System.Drawing.Point(183, 56);
            this.TitleEXP.Name = "TitleEXP";
            this.TitleEXP.Size = new System.Drawing.Size(163, 37);
            this.TitleEXP.TabIndex = 1;
            this.TitleEXP.Text = "EXPEDIENTE";
            // 
            // SendButton
            // 
            this.SendButton.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.SendButton.Font = new System.Drawing.Font("Franklin Gothic Book", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SendButton.Location = new System.Drawing.Point(217, 201);
            this.SendButton.Name = "SendButton";
            this.SendButton.Size = new System.Drawing.Size(86, 24);
            this.SendButton.TabIndex = 2;
            this.SendButton.Text = "Enviar";
            this.SendButton.UseVisualStyleBackColor = true;
            this.SendButton.Click += new System.EventHandler(this.SendButton_Click);
            // 
            // AdminButton
            // 
            this.AdminButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.AdminButton.Font = new System.Drawing.Font("Franklin Gothic Book", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AdminButton.Location = new System.Drawing.Point(8, 270);
            this.AdminButton.Name = "AdminButton";
            this.AdminButton.Size = new System.Drawing.Size(169, 40);
            this.AdminButton.TabIndex = 3;
            this.AdminButton.Text = "Modo Administrador";
            this.AdminButton.UseVisualStyleBackColor = true;
            this.AdminButton.Click += new System.EventHandler(this.AdminButton_Click);
            // 
            // RegistLabel
            // 
            this.RegistLabel.ActiveLinkColor = System.Drawing.Color.Black;
            this.RegistLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.RegistLabel.AutoSize = true;
            this.RegistLabel.Font = new System.Drawing.Font("Franklin Gothic Book", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RegistLabel.LinkColor = System.Drawing.Color.White;
            this.RegistLabel.Location = new System.Drawing.Point(210, 172);
            this.RegistLabel.Name = "RegistLabel";
            this.RegistLabel.Size = new System.Drawing.Size(101, 17);
            this.RegistLabel.TabIndex = 4;
            this.RegistLabel.TabStop = true;
            this.RegistLabel.Text = "Realizar Registro";
            this.RegistLabel.VisitedLinkColor = System.Drawing.Color.Silver;
            this.RegistLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.RegistLabel_LinkClicked);
            // 
            // Principal
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(534, 321);
            this.Controls.Add(this.RegistLabel);
            this.Controls.Add(this.AdminButton);
            this.Controls.Add(this.SendButton);
            this.Controls.Add(this.TitleEXP);
            this.Controls.Add(this.TextBoxExp);
            this.MinimumSize = new System.Drawing.Size(550, 360);
            this.Name = "Principal";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Almacen Automatizacion";
            this.Load += new System.EventHandler(this.Principal_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox TextBoxExp;
        private System.Windows.Forms.Label TitleEXP;
        private System.Windows.Forms.Button SendButton;
        private System.Windows.Forms.Button AdminButton;
        private System.Windows.Forms.LinkLabel RegistLabel;
    }
}

