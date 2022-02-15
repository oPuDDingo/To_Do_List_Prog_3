import {AfterViewInit, Component, ElementRef, EventEmitter, Input, OnInit, Output, ViewChild} from '@angular/core';
import {Reminder} from "../../data-access/models/reminder";

@Component({
  selector: 'reminder',
  templateUrl: './reminder.component.html',
  styleUrls: ['./reminder.component.scss']
})
export class ReminderComponent implements OnInit, AfterViewInit {

  @Input()
  reminder : Reminder;
  date : string;


  @Output()
  updateEvent: EventEmitter<Reminder> = new EventEmitter<Reminder>();

  @Output()
  deleteEvent: EventEmitter<Reminder> = new EventEmitter<Reminder>();

  @ViewChild('title')
  inputField : ElementRef;

  @ViewChild('flag')
  flagImg : ElementRef;

  @ViewChild('flagbtn')
  flagIBtn : ElementRef;

  @ViewChild('date')
  inputDate : ElementRef;

  constructor() { }

  ngOnInit(): void {
  }

  ngAfterViewInit() {
    this.inputField.nativeElement.focus();
    this.setFlagIcon();
  }

  toggleFlag() {
    this.reminder.flagged = !this.reminder.flagged;
    this.setFlagIcon();
    this.triggerUpdate();
  }

  setFlagIcon(){
    if(this.reminder.flagged) {
      this.flagImg.nativeElement.setAttribute("src", "/assets/markTrue.png");
      this.flagIBtn.nativeElement.setAttribute("class", "reminder-button flag true");
    }
    else {
      this.flagImg.nativeElement.setAttribute("src", "/assets/markFalse.png");
      this.flagIBtn.nativeElement.setAttribute("class", "reminder-button flag false");
    }
  }

  triggerUpdate(){
    this.updateEvent.emit(this.reminder);
  }

  triggerDelete(){
    this.deleteEvent.emit(this.reminder);
  }


}
