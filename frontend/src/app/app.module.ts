import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { BoardComponent } from '../lib/feature/board/board.component';
import { ListComponent } from '../lib/feature/list/list.component';
import { ReminderComponent } from '../lib/feature/reminder/reminder.component';
import { ToolbarComponent } from "../lib/ui/toolbar/toolbar.component";
import {FormsModule} from "@angular/forms";
import {FocusDirective} from "../lib/util/autofocus.directive";
import {HttpClientModule} from "@angular/common/http";



@NgModule({
  declarations: [AppComponent, BoardComponent, ListComponent, ReminderComponent, ToolbarComponent, FocusDirective],
  imports: [BrowserModule, AppRoutingModule, FormsModule, HttpClientModule],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
