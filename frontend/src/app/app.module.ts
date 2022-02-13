import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { BoardComponent } from './board/board.component';
import { ListComponent } from './list/list.component';
import { ReminderComponent } from './reminder/reminder.component';
import { ToolbarComponent } from "../lib/ui/toolbar/toolbar.component";
import {FormsModule} from "@angular/forms";



@NgModule({
  declarations: [AppComponent, BoardComponent, ListComponent, ReminderComponent, ToolbarComponent],
  imports: [BrowserModule, AppRoutingModule, FormsModule],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
