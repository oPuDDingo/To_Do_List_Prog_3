import {AfterViewInit, Component, ElementRef, EventEmitter, Input, OnInit, Output, ViewChild} from '@angular/core';
import {Reminder} from "../../lib/data-access/models/reminder";

@Component({
  selector: 'app-reminder',
  templateUrl: './reminder.component.html',
  styleUrls: ['./reminder.component.scss']
})
export class ReminderComponent implements OnInit, AfterViewInit {

  @Input()
  reminder : Reminder;
  date : string;

  @Output()
  deleteClicked: EventEmitter<Reminder> = new EventEmitter<Reminder>();

  @ViewChild('title')
  inputField : ElementRef;

  @ViewChild('flag')
  flagImg : ElementRef;

  @ViewChild('flagbtn')
  flagIBtn : ElementRef;

  @ViewChild('date')
  inputeDate : ElementRef;

  constructor() { }

  ngOnInit(): void {
  }

  ngAfterViewInit() {
    this.inputField.nativeElement.focus();
  }

  onFlagClicked() {
    this.reminder.flagged = !this.reminder.flagged;
    if(this.reminder.flagged) {
      this.flagImg.nativeElement.setAttribute("src", "/assets/markTrue.png");
      this.flagIBtn.nativeElement.setAttribute("class", "reminder-button flag true");
    }
    else {
      this.flagImg.nativeElement.setAttribute("src", "/assets/markFalse.png");
      this.flagIBtn.nativeElement.setAttribute("class", "reminder-button flag false");
    }
  }

  onDeleteClicked(){
    this.deleteClicked.emit(this.reminder);
  }

  updateDate(){

  }

}
