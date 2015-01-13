namespace MusicGameServer
{
    partial class MusicGameForm
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
            this.components = new System.ComponentModel.Container();
            this.readMessageTimer = new System.Windows.Forms.Timer(this.components);
            this.btnReset = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.comboBoxPorts = new System.Windows.Forms.ComboBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.tbCurrentMsg = new System.Windows.Forms.TextBox();
            this.lblStatus = new System.Windows.Forms.Label();
            this.lblScore = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // readMessageTimer
            // 
            this.readMessageTimer.Tick += new System.EventHandler(this.readMessageTimer_Tick);
            // 
            // btnReset
            // 
            this.btnReset.Location = new System.Drawing.Point(92, 12);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(75, 23);
            this.btnReset.TabIndex = 3;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(11, 12);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 4;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // comboBoxPorts
            // 
            this.comboBoxPorts.FormattingEnabled = true;
            this.comboBoxPorts.Location = new System.Drawing.Point(12, 199);
            this.comboBoxPorts.Name = "comboBoxPorts";
            this.comboBoxPorts.Size = new System.Drawing.Size(121, 21);
            this.comboBoxPorts.TabIndex = 6;
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(11, 226);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(75, 23);
            this.btnConnect.TabIndex = 7;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // btnRefresh
            // 
            this.btnRefresh.Location = new System.Drawing.Point(92, 226);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(75, 23);
            this.btnRefresh.TabIndex = 8;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // tbCurrentMsg
            // 
            this.tbCurrentMsg.Location = new System.Drawing.Point(12, 117);
            this.tbCurrentMsg.Name = "tbCurrentMsg";
            this.tbCurrentMsg.Size = new System.Drawing.Size(100, 20);
            this.tbCurrentMsg.TabIndex = 9;
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.Location = new System.Drawing.Point(8, 140);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(55, 13);
            this.lblStatus.TabIndex = 10;
            this.lblStatus.Text = "Messages";
            // 
            // lblScore
            // 
            this.lblScore.AutoSize = true;
            this.lblScore.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblScore.Location = new System.Drawing.Point(12, 62);
            this.lblScore.Name = "lblScore";
            this.lblScore.Size = new System.Drawing.Size(87, 25);
            this.lblScore.TabIndex = 11;
            this.lblScore.Text = "Score: ";
            // 
            // MusicGameForm
            // 
            this.AcceptButton = this.btnConnect;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(183, 261);
            this.Controls.Add(this.lblScore);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.tbCurrentMsg);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.comboBoxPorts);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.btnReset);
            this.Name = "MusicGameForm";
            this.Text = "Music Game";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MusicGameForm_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer readMessageTimer;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ComboBox comboBoxPorts;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.TextBox tbCurrentMsg;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Label lblScore;
    }
}

